#define LINES_TO_READ 10
#define ERROR -1
#define PERMS 0644

//typedef = allows us to descirbe our own data type.
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef int FD;

int main(int ac, char* args[]) {

    //If no arguments are given print error.
    if(ac < 2) {
        write(2, "no agruments given.\n", 21);
        exit(EXIT_FAILURE);
    }
    FD fd_source = open(args[1], O_RDONLY); //open the source file.
//If source failed to open print error msg and quit.
    if(fd_source == ERROR) {
        write(2, "Failed to open file.\n", 22);
        exit(EXIT_FAILURE);
    }
    //Open the destination file to write in.
    FD fd_dest = open(args[1], O_WRONLY, PERMS);

     //verify that the destination file was opened.
    if(fd_dest == ERROR) {
        // if file failed to open, quit and print error msg.
        write(2, "failed to open destination file.\n", 34);
        exit(EXIT_FAILURE);//quit...

    }
    //Declare a buffer and ch array to read the files line by line.
    char ch, buffer[128];
    int bytes_read = 0;
    int write_result;
    int lines = 1; //variable to count the number of lines read.
    int index;

    //While bytes read is greater than 0, read from the source file.
    while((bytes_read = read(fd_source, &ch, 1)) > 0) {
        //scan the characters and put it in buffer.
        if(ch == '\n') {
            buffer[index] = ch;
            buffer[index+1] = '\0'; //stop buffer at the end of the string.
            index = 0; //set the index to 0.
            
            write_result = 0;
            int buff_len = strlen(buffer);
            while(write_result != buff_len) {
                //write the data of size buff_len from buffer and store it in variable.
                int res = write(STDOUT_FILENO, buffer + write_result, buff_len - write_result);
                
                //If the write failed quit and print error msg.
                if(write_result < 0) {
                    write(2, "Failed to write.\n",18);
                    exit(EXIT_FAILURE);

                }
                //copy the written data in write_result.
                write_result += res;
                
            }
            //If 10 lines written break;
            if (lines == LINES_TO_READ) {
                break;
            }
            lines++;
        } else {
            //Else keep writing
            buffer[index++] = ch;
        }
    }

//    If ever error occurs during read and write quit and print error msg.
      if (bytes_read == ERROR || write_result == ERROR) {
          write(fd_source, buffer, bytes_read);
          exit(EXIT_FAILURE);
      }
       //Attempt to close the files.
      if(close(fd_source) == ERROR) {
          write(fd_source, buffer, bytes_read);
          //Note use more descripter.
          exit(EXIT_FAILURE);
      }
//       //If the atte
    return 0;

}

