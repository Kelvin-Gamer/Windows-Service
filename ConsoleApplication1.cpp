#include <windows.h>
#include <tchar.h>

#define SERVICE_NAME _T("WinHttpSvc")

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

// Declara��o das fun��es
void ServiceMain(int argc, TCHAR* argv[]);
void ControlHandler(DWORD request);
void start(HINSTANCE handle);

int _tmain(int argc, TCHAR* argv[]) {
    SERVICE_TABLE_ENTRY ServiceTable[2] = { { NULL, NULL }, { NULL, NULL } };

    ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
    ServiceTable[0].lpServiceName = _tcsdup(SERVICE_NAME); // Faz uma c�pia mut�vel do nome do servi�o

    // Inicia o despacho do servi�o, permitindo que o servi�o responda a eventos do controle do gerenciador de servi�o
    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}

// Fun��o principal do servi�o, chamada quando o servi�o � iniciado
void ServiceMain(int argc, TCHAR* argv[]) {
    // Configura o estado inicial do servi�o como "inicializa��o pendente"
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    // Registra o manipulador de controle do servi�o
    hStatus = RegisterServiceCtrlHandler(SERVICE_NAME, (LPHANDLER_FUNCTION)ControlHandler);

    // Verifica se a opera��o de registro foi bem-sucedida
    if (hStatus == (SERVICE_STATUS_HANDLE)NULL)
        return;

    // Chama a fun��o "start" para realizar a inicializa��o do servi�o
    start(NULL);

    // Finaliza o processo do servi�o
    ExitProcess(0);
}

// Manipulador de controle do servi�o, chamado quando o servi�o recebe um comando do gerenciador de servi�o
void ControlHandler(DWORD request) {
    switch (request) {
    case SERVICE_CONTROL_STOP:
        // Define o c�digo de sa�da como 0 e o estado atual como "parado"
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        // Atualiza o status do servi�o com a nova configura��o
        SetServiceStatus(hStatus, &ServiceStatus);
        return;

    case SERVICE_CONTROL_SHUTDOWN:
        // Define o c�digo de sa�da como 0 e o estado atual como "parado"
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        // Atualiza o status do servi�o com a nova configura��o
        SetServiceStatus(hStatus, &ServiceStatus);
        return;

    default:
        break;
    }
    return;
}

// Fun��o "start" que realiza a inicializa��o do servi�o
void start(HINSTANCE handle) {
    // Implementa��o vazia, esta fun��o � um espa�o reservado para a inicializa��o do servi�o.
    // Aqui voc� pode adicionar o c�digo real para a inicializa��o do servi�o.
    // Esta fun��o � chamada quando o servi�o � iniciado e pode ser utilizada para executar
    // quaisquer tarefas necess�rias para o funcionamento correto do servi�o.
}
