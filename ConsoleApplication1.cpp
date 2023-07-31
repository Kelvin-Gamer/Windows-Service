#include <windows.h>
#include <tchar.h>

#define SERVICE_NAME _T("WinHttpSvc")

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

// Declaração das funções
void ServiceMain(int argc, TCHAR* argv[]);
void ControlHandler(DWORD request);
void start(HINSTANCE handle);

int _tmain(int argc, TCHAR* argv[]) {
    SERVICE_TABLE_ENTRY ServiceTable[2] = { { NULL, NULL }, { NULL, NULL } };

    ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
    ServiceTable[0].lpServiceName = _tcsdup(SERVICE_NAME); // Faz uma cópia mutável do nome do serviço

    // Inicia o despacho do serviço, permitindo que o serviço responda a eventos do controle do gerenciador de serviço
    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}

// Função principal do serviço, chamada quando o serviço é iniciado
void ServiceMain(int argc, TCHAR* argv[]) {
    // Configura o estado inicial do serviço como "inicialização pendente"
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    // Registra o manipulador de controle do serviço
    hStatus = RegisterServiceCtrlHandler(SERVICE_NAME, (LPHANDLER_FUNCTION)ControlHandler);

    // Verifica se a operação de registro foi bem-sucedida
    if (hStatus == (SERVICE_STATUS_HANDLE)NULL)
        return;

    // Chama a função "start" para realizar a inicialização do serviço
    start(NULL);

    // Finaliza o processo do serviço
    ExitProcess(0);
}

// Manipulador de controle do serviço, chamado quando o serviço recebe um comando do gerenciador de serviço
void ControlHandler(DWORD request) {
    switch (request) {
    case SERVICE_CONTROL_STOP:
        // Define o código de saída como 0 e o estado atual como "parado"
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        // Atualiza o status do serviço com a nova configuração
        SetServiceStatus(hStatus, &ServiceStatus);
        return;

    case SERVICE_CONTROL_SHUTDOWN:
        // Define o código de saída como 0 e o estado atual como "parado"
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        // Atualiza o status do serviço com a nova configuração
        SetServiceStatus(hStatus, &ServiceStatus);
        return;

    default:
        break;
    }
    return;
}

// Função "start" que realiza a inicialização do serviço
void start(HINSTANCE handle) {
    // Implementação vazia, esta função é um espaço reservado para a inicialização do serviço.
    // Aqui você pode adicionar o código real para a inicialização do serviço.
    // Esta função é chamada quando o serviço é iniciado e pode ser utilizada para executar
    // quaisquer tarefas necessárias para o funcionamento correto do serviço.
}
