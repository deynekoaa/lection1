#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

/* нужно для сравнения строк */
#include <string.h>

void worker(char *input)
{
	/* буфер для хранения ответа пользователя */
	char *answer;
	/* сравнение строк по очереди для поиска известной команды */
	if(strncasecmp(input, "strlen", 6) == 0)
	{
		answer = readline("Введите любую строку: ");
		if(NULL == answer)
			exit(0);
		/* strlen возвращает size_t, поэтому %zd, а не просто %d */
		printf("Число символов в строке: %zd\n", strlen(answer));
		free(answer);
	}
	else if(strncasecmp(input, "cat", 3) == 0)
	{
		answer = readline("Введите имя файла (используйте TAB): ");
		if(NULL == answer)
			exit(0);
		/* открываем файл на чтение в текстовом режиме */
		FILE *f = fopen(answer, "rt");
		if(f)
		{
			char *line = NULL;
			size_t len = 0;
			/* getline крайне рекомендуется для чтения текстового файла построчно */
			/* она работает с динамической памятью, что безопаснее, чем fgets/gets */
			/* это гарантирует чтение любого файла с произвольной длиной строки */
			while(getline(&line, &len, f) != -1)
				/* ещё один способ вывода строки в терминал */
				fputs(line, stdout);
			/* после getline также надо чистить память! */
			if(line)
				free(line);
			/* не забываем "закрыть" файл */
			fclose(f);
		}
		else
		{
			puts("Файл не найден!");
		}
		free(answer);
	}
	else if(strncasecmp(input, "quit", 4) == 0 || strncasecmp(input, "exit", 4) == 0)
	{
		puts("До встречи!");
		exit(0);
	}
	else
	{
		if(strncasecmp(input, "help", 4) != 0)
			printf("Неизвестная команда: %s\n", input);
		help();
	}
}
