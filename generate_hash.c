#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* host_CudaCrypt(char* rawPassword){
    static char newP[11];
    newP[0] = rawPassword[0] + 3;
    newP[1] = rawPassword[0] - 2;
    newP[2] = rawPassword[0] + 1;
    newP[3] = rawPassword[1] + 1;
    newP[4] = rawPassword[1] - 2;
    newP[5] = rawPassword[1] - 3;
    newP[6] = rawPassword[2] + 1;
    newP[7] = rawPassword[2] - 2;
    newP[8] = rawPassword[3] + 4;
    newP[9] = rawPassword[3] - 3;
    newP[10] = '\0';

    for(int i=0;i<10;i++){
        if(i >= 0 && i < 6){
            if(newP[i] > 122){ newP[i] = (newP[i] - 122) + 97 - 1; }
            else if(newP[i] < 97){ newP[i] = 122 - (97 - newP[i] - 1); }
        } else {
            if(newP[i] > 57){ newP[i] = (newP[i] - 57) + 48 - 1; }
            else if(newP[i] < 48){ newP[i] = 57 - (48 - newP[i] - 1); }
        }
    }
    return newP;
}

int main(int argc, char ** argv){
    if (argc < 2 || strlen(argv[1]) != 4) {
        printf("Usage: %s <password>\n", argv[0]);
        printf("Password must be 2 lowercase letters and 2 numbers (e.g., ab12)\n");
        return 1;
    }
    char *encryptedPass = host_CudaCrypt(argv[1]);
    printf("%s\n", encryptedPass);
    return 0;
}
