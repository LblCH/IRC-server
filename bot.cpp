#include <stdio.h>
#include <string.h>

#define PORT 6667
#define SERVERADDR "127.0.0.1" //Звёздочками пометил свой IP

int main(int argc, char* argv[])
{
    char buff[1024];
    printf("TCP DEMO CLIENT\n");

    // Шаг 2 - создание сокета
    SOCKET my_sock;
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0)
    {
        printf("Socket() error\n");
        return -1;
    }

    // Шаг 3 - установка соединения
    // заполнение структуры sockaddr_in - указание адреса и порта сервера
    sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    HOSTENT *hst;

    // преобразование IP адреса из символьного в сетевой формат
    if (inet_addr(SERVERADDR) != INADDR_NONE)
        dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
    {
        // попытка получить IP адрес по доменному имени сервера
        if (hst = gethostbyname(SERVERADDR))
            // hst->h_addr_list содержит не массив адресов,
            // а массив указателей на адреса
            ((unsigned long *)&dest_addr.sin_addr)[0] =
                    ((unsigned long **)hst->h_addr_list)[0][0];
        else
        {
            printf("Invalid address %s\n", SERVERADDR);
            closesocket(my_sock);
            return -1;
        }
    }

    // адрес сервера получен - пытаемся установить соединение
    if (connect(my_sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
    {
        printf("Connect error\n");
        return -1;
    }

    printf("Soedinenie s %s uspeshno ustanovlenno\n \
            Type quit for quit\n\n", SERVERADDR);

    // Шаг 4 - чтение и передача сообщений
    int nsize;
    while ((nsize = recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) != SOCKET_ERROR)
    {
        // ставим завершающий ноль в конце строки
        buff[nsize] = 0;

        // выводим на экран
        printf("S=>C:%s", buff);

        // читаем пользовательский ввод с клавиатуры
        printf("S<=C:"); fgets(&buff[0], sizeof(buff) - 1, stdin);

        // проверка на "quit"
        if (!strcmp(&buff[0], "quit\n"))
        {
            // Корректный выход
            printf("Exit...");
            closesocket(my_sock);
            return 0;
        }

        // передаем строку клиента серверу
        send(my_sock, &buff[0], strlen(&buff[0]), 0);
    }
    printf("Recv error\n");
    closesocket(my_sock);
    return -1;
}