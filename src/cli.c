#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graphics.h"
#include "debug.h"
#include "cli.h"

bool quit = false;

void print_version()
{
	printf("Metaballs %s - Author: github.com/upperdim\n", VERSION);
}

void print_help()
{
	print_version();
	printf("\nArguments:\n");
	printf("  -h, -H, --help       Prints this hint.\n");
	printf("  -v, -V, --version    Prints the version of the binary.\n");
	printf("  -d, -D, --debug      Runs the binary in debugging mode. Draws\n");
	printf("                           ball positions and framerate. Indicates \n");
	printf("                           upon window resizing and frame limiter toggle.\n");
	printf("  -l, -L               Limits framerate to 60.\n\n");
}

void handle_args(int *argc, char **argv)
{
	for (int i = 1; i < *argc; ++i) {
		if      (strcmp("--help",    argv[i]) == 0) {print_help();    quit = true;}
		else if (strcmp("--version", argv[i]) == 0) {print_version(); quit = true;}
		else if (strcmp("--debug",   argv[i]) == 0) {debugMode = true;}
		else if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h':
			case 'H':
				print_help();
				quit = true;
			case 'v':
			case 'V':
				print_version();
				quit = true;
			case 'd':
			case 'D':
				debugMode = true;
				break;
			case 'l':
			case 'L':
				limitFramerate = true;
				break;
			default:
				printf("%s: Unrecognized option '%s'\nTry '%s --help' for more information.\n", argv[0], argv[i], argv[0]);
				quit = true;;
			}
		} else {
			printf("%s: Unrecognized option '%s'\nTry '%s --help' for more information.\n", argv[0], argv[i], argv[0]);
			quit = true;;
		}
	}
}
