#define LINES_TO_READ 10

//typedef = allows us to descirbe our own data type.
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef int FD;

int main(int ac, char* args[]) {
//    char* filename;
//    //Give pointer to read from args[i].
//    for(int i=0; i<ac; i++) {
//        filename = args[i];
//    }

    if(ac < 2) {
        write(2, "no agruments given.\n", 21);
        exit(EXIT_FAILURE);
    }
    FD fd_source = open(args[1], O_RDONLY); //open the source file.

    if(fd_source == -1) {
        write(2, "Failed to open file.\n", 22);
        exit(EXIT_FAILURE);
    }
    FD fd_dest = open(args[1], O_WRONLY, 0644); //third arg = permissions for file.
    //permissions are manipulated for using octal.

     //verify that the destination file was opened.
    if(fd_dest == -1) {
        // if file failed to open, quit and print error msg.
        write(2, "failed to open destination file.\n", 34);
        exit(EXIT_FAILURE);//quit...

    }
    //Declare a buffer and ch array to read the files line by line.
    char ch, buffer[128];
    int bytes_read = 0;
    int write_result;
    int lines = 1; //variable to count the number of lines read.
    int index = 0;
//While something is read, write it.
    while((bytes_read = read(fd_source, &ch, 1)) > 0) {
        write_result = write(fd_source, buffer, bytes_read);

        if(ch == '\n') {
            buffer[index] = ch;
            buffer[index+1] = '\0';
//
//            write_result = 0;
            int buff_length = strlen(buffer);
            while(write_result != buff_length) {
                int res = write(STDOUT_FILENO, buffer + write_result, buff_length-write_result);

                if(write_result < 0) {
                    write(2, "Failed to write.\n",18);
                    exit(EXIT_FAILURE);

                }
                write_result += res;

            }
            if (lines == LINES_TO_READ) {
                break;
            }
            lines++;
        } else {
            buffer[index++] = ch;
        }

//           if(write_result == -1) {
//               break;
//           }
    }

//    If ever error occurs during read and write quit and print error msg.
//      if (bytes_read == -1 || write_result == -1) {
//          write(fd_source, buffer, bytes_read);
//          exit(EXIT_FAILURE);
//      }
       //Attempt to close the files.
      if(close(fd_source) == -1 || close(fd_source) == -1) {
          write(fd_source, buffer, bytes_read);
          //Note use more descripter.
          exit(EXIT_FAILURE);
      }
//       //If the atte
    return 0;

}



