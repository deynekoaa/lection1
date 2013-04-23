/* для radline */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

/* парсер аргументов */
#include <getopt.h>

/* Дополнительные файлы */
#include "readline.h"

int main(int argc, char **argv)
{
	/* Строка приглашения ввода пользователя, можно изменить или формировать динамически */
	const char std_prompt[] = "Введите команду: ";
	char *input;
	/* парсер аргументов командной строки */
	int c;
	int option_index = 0;
	/* внутренний флаг ведения истории, по умолчанию включён */
	static int history = 1;
	static struct option long_options[] = {
		{"exec-command",	required_argument,	0, 'x'},
		{"help",		no_argument,		0, 'h'},
		{"no-history",		no_argument,		0, 'n'},
		{0, 0, 0, 0}
	};
	while((c = getopt_long(argc, argv, "nhx:",
		long_options, &option_index)) != -1)
	{
		switch(c)
		{
			case 'n':
				/* выключаем флаг ведения истории */
				history = 0;
				break;
			case 'h':
				help();
				exit(0);
			case 'x':
				worker(optarg);
				break;
		}
	}
	/* цикл диалога с пользователем */
	for(;;)
	{
		/* Запрашиваем ввод пользователя */
		input = readline(std_prompt);
		/* конец диалога - выход */
		if (NULL == input)
			break;

		/* Добавить предыдущий ввод в историю (если разрешено) */
		if(history)
			add_history(input);

		/* Выполняем полезную работу */
		worker(input);

		/* Полученную строку от readline необходимо освободить, так как память сама не очищается */
		free(input);
	}
	return 0;
}
