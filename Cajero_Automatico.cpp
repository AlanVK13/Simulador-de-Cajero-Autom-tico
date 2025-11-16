#include <iostream>
#include <string>       // Para usar strings
#include <iomanip>      // Para std::setprecision y std::fixed (formato de dinero)
#include <stdexcept>    // Para std::invalid_argument en el manejo de excepciones
#include <limits>       // Para std::numeric_limits (limpiar buffer de cin)

// Usamos namespace std para no tener que escribir std:: en todos lados
using namespace std;

// --- 1. Definición de la Estructura ---
// Requisito: "Uso de estructuras para representar cuentas."
struct Account {
    string accountNumber;
    string holderName;
    double balance;
    string pin; // Un PIN simple para la simulación
};

// --- 2. Prototipos de Funciones ---
// Requisito: "Uso de funciones para cada operación."
Account* login(Account accounts[], int numAccounts);
void showMenu(Account* loggedInAccount, Account accounts[], int numAccounts);
void checkBalance(Account* acc);
void deposit(Account* acc);
void withdraw(Account* acc);
void transfer(Account* fromAcc, Account accounts[], int numAccounts);
Account* findAccount(const string& accNumber, Account accounts[], int numAccounts);
double getValidAmount(); // Función especial para manejar excepciones de entrada

// Constante para el número de cuentas
const int NUM_ACCOUNTS = 3;

// --- 3. Función Principal (main) ---
int main() {
    // Requisito: "Mínimo 3 cuentas simuladas con saldo inicial."
    // Requisito: "Uso de... arreglos."
    Account accounts[NUM_ACCOUNTS] = {
        {"12345", "Juan Perez", 1500.75, "1111"},
        {"67890", "Maria Lopez", 500.20, "2222"},
        {"11223", "Carlos Sanchez", 2800.00, "3333"}
    };

    // Configura cout para mostrar 2 decimales para el dinero
    cout << fixed << setprecision(2);

    cout << "--- Bienvenido al Simulador de Cajero Automatico ---" << endl;

    // Requisito: "Control de flujo: ... repetición."
    Account* currentUser = nullptr;
    while (currentUser == nullptr) {
        currentUser = login(accounts, NUM_ACCOUNTS);
        if (currentUser == nullptr) {
            cout << "Error: Numero de cuenta o PIN incorrecto. Intente de nuevo." << endl;
        }
    }

    cout << "\n¡Login exitoso! Bienvenido, " << currentUser->holderName << "." << endl;

    // Mostrar el menú principal
    showMenu(currentUser, accounts, NUM_ACCOUNTS);

    cout << "Gracias por usar el simulador. ¡Adios!" << endl;
    return 0;
}

// --- 4. Implementación de Funciones ---

/**
 * @brief Solicita al usuario número de cuenta y PIN.
 * @return Un puntero a la cuenta si el login es exitoso, o nullptr si falla.
 * Requisito: "Uso de... punteros."
 */
Account* login(Account accounts[], int numAccounts) {
    string number, pin;
    cout << "\nIngrese su numero de cuenta: ";
    cin >> number;
    cout << "Ingrese su PIN: ";
    cin >> pin;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == number && accounts[i].pin == pin) {
            return &accounts[i]; // Devuelve la dirección de memoria de la cuenta
        }
    }
    return nullptr; // No se encontró la cuenta
}

/**
 * @brief Muestra el menú principal y maneja la selección del usuario.
 * Requisito: "Menú interactivo con opciones."
 */
void showMenu(Account* loggedInAccount, Account accounts[], int numAccounts) {
    int choice;
    // Requisito: "Control de flujo: ... repetición." (do-while)
    do {
        cout << "\n--- Menu Principal ---" << endl;
        cout << "1. Consultar Saldo" << endl;
        cout << "2. Depositar" << endl;
        cout << "3. Retirar" << endl;
        cout << "4. Transferir" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        // Validación simple de entrada (no es la de excepciones, solo para el menú)
        while (!(cin >> choice)) {
            cout << "Opcion invalida. Intente de nuevo: ";
            cin.clear(); // Limpia el flag de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada incorrecta
        }

        // Requisito: "Control de flujo: selección." (switch)
        switch (choice) {
            case 1:
                checkBalance(loggedInAccount);
                break;
            case 2:
                deposit(loggedInAccount);
                break;
            case 3:
                withdraw(loggedInAccount);
                break;
            case 4:
                transfer(loggedInAccount, accounts, numAccounts);
                break;
            case 5:
                // Requisito: "Control de flujo: ... salto." (break implícito para salir)
                break;
            default:
                cout << "Opcion no valida. Por favor intente de nuevo." << endl;
        }

    } while (choice != 5);
}

/**
 * @brief Muestra el saldo de la cuenta.
 */
void checkBalance(Account* acc) {
    cout << "\n--- Consulta de Saldo ---" << endl;
    cout << "Su saldo actual es: $" << acc->balance << endl;
}

/**
 * @brief Añade fondos a la cuenta.
 */
void deposit(Account* acc) {
    cout << "\n--- Depósito ---" << endl;
    double amount = getValidAmount(); // Pide un monto usando la función con excepciones
    if (amount > 0) {
        acc->balance += amount; // Modifica el valor usando el puntero
        cout << "Deposito exitoso." << endl;
        cout << "Nuevo saldo: $" << acc->balance << endl;
    }
}

/**
 * @brief Retira fondos de la cuenta.
 * Requisito: "Validación de montos y saldo insuficiente."
 */
void withdraw(Account* acc) {
    cout << "\n--- Retiro ---" << endl;
    double amount = getValidAmount();
    if (amount > 0) {
        if (amount <= acc->balance) {
            acc->balance -= amount; // Modifica el valor usando el puntero
            cout << "Retiro exitoso." << endl;
            cout << "Nuevo saldo: $" << acc->balance << endl;
        } else {
            cout << "Error: Saldo insuficiente." << endl;
        }
    }
}

/**
 * @brief Transfiere fondos a otra cuenta.
 */
void transfer(Account* fromAcc, Account accounts[], int numAccounts) {
    cout << "\n--- Transferencia ---" << endl;
    string targetAccountNumber;
    cout << "Ingrese el numero de cuenta destino: ";
    cin >> targetAccountNumber;

    // Buscar la cuenta destino
    Account* toAcc = findAccount(targetAccountNumber, accounts, numAccounts);

    if (toAcc == nullptr) {
        cout << "Error: La cuenta destino no existe." << endl;
    } else if (toAcc->accountNumber == fromAcc->accountNumber) {
        cout << "Error: No puede transferir a su propia cuenta." << endl;
    } else {
        // Si la cuenta existe, pedir el monto
        double amount = getValidAmount();
        if (amount > 0) {
            // Requisito: "Validación de ... saldo insuficiente."
            if (amount <= fromAcc->balance) {
                // Realizar la transferencia
                fromAcc->balance -= amount;
                toAcc->balance += amount;
                cout << "Transferencia exitosa." << endl;
                cout << "Su nuevo saldo: $" << fromAcc->balance << endl;
            } else {
                cout << "Error: Saldo insuficiente para transferir." << endl;
            }
        }
    }
}

/**
 * @brief Busca una cuenta por su número.
 * @return Un puntero a la cuenta si se encuentra, o nullptr si no.
 */
Account* findAccount(const string& accNumber, Account accounts[], int numAccounts) {
    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNumber) {
            return &accounts[i]; // Devuelve el puntero
        }
    }
    return nullptr;
}

/**
 * @brief Pide al usuario un monto y valida que sea un número positivo.
 * Requisito: "Manejo de excepciones para entradas inválidas."
 * @return El monto validado.
 */
double getValidAmount() {
    string input;
    double amount;
    while (true) {
        cout << "Ingrese el monto: $";
        cin >> input;
        
        // Requisito: "Uso de... excepciones."
        try {
            amount = stod(input); // Convierte string a double. Lanza excepción si no es número.
            
            if (amount <= 0) {
                cout << "Error: El monto debe ser un número positivo." << endl;
            } else {
                return amount; // El monto es válido, salimos del bucle
            }
        } catch (const invalid_argument& e) {
            // Esto se ejecuta si el usuario escribe "abc" o algo no numérico
            cout << "Error: Entrada invalida. Por favor ingrese solo numeros." << endl;
        } catch (const out_of_range& e) {
            // Esto se ejecuta si el número es demasiado grande
            cout << "Error: El monto esta fuera de rango." << endl;
        }
    }
}