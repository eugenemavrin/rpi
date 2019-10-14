#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {

    	struct termios serial;
    	char str[100] = "default";
	char arg;
    	char buffer[100];
	printf("\nprint 'h' for help\n\n");
    	int fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);

    	if (fd > 0) {

    		// Set up Serial Configuration
        	serial.c_iflag = 0;
		serial.c_cflag &=  ~PARENB;
		serial.c_cflag &=  ~CSTOPB;
		serial.c_cflag |=  CS8;
		serial.c_cflag &=  ~CRTSCTS;
		serial.c_lflag =   0;
		serial.c_oflag =   0;
		//serial.c_cflag = 0;

		serial.c_cc[VMIN] = 0;
		serial.c_cc[VTIME] = 5;

        	serial.c_cflag = B9600 | CS8 | CREAD;

        	tcsetattr(fd, TCSANOW, &serial); // Apply
		/*
		 * t - transmit
		 * r - receive
		 * x - exit
		*/
		printf("\nenter new command : ");
		while (1) {
			scanf("%c", &arg);
			switch(arg) {
				case 't':
				{
					printf("\nMessage for transmit: ");
					scanf("%s", str);
					int wcount = write(fd, str, strlen(str));
					if(wcount > -1)
						printf ("\n%d symbols was transmitted successfully", wcount);
					printf("\nenter new command : ");
					break;
				}
				case 'r':
				{
					printf("\nWaiting for receive message...:\n");
					int rcount = 0;
                			do rcount = read(fd, buffer, sizeof(buffer));
                			while (rcount <= 0);
					printf("\n%d symbols was received successfully\n", rcount - 1);
					buffer[rcount] = '\0';
					printf("\nMessage: %s\n", buffer);
					printf("\nenter new command : ");
					break;
				}
				case 'x':
				{
					printf("\nexit\n");
					close(fd);
					return 0;
					break;
				}
				case 'h':
					printf("\n\n't' - transmit data via serial0\n'r' - receive data via serial0\n'x' - exit\n");
					printf("\nenter new command : ");
					break;
				default:
					break;
			}
		}
	}
}
 


