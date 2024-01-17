/*
 * Implementasi Caesar Cipher di C
 * GCC/CLANG versi 17.0.6
 * build aarch64-unknown-linux-android24
 * Lisensi : GNU Public License
 */

#include <stdio.h>  // standar i/o stream
#include <stdlib.h> // standar alokasi memori ke char* / char[]
#include <string.h> // standar string utility
#include <time.h>   // standar time formatting

// text color
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define BLUE "\e[1;34m"
#define CYAN "\e[1;36m"
#define YELLOW "\e[1;33m"
#define PURPLE "\e[1;35m"
#define WHITE "\e[0m"

char *encrypt(char *unencrypted, int tokens) {

  // alokasi memori sesuai jumlah char
  char *encrypted = malloc(sizeof(unencrypted));
  char space = '_'; // separator

  // iterasi dasar
  for (int i = 0; i < strlen(unencrypted); i++) {

    // jika string[i] adalah separator
    if (unencrypted[i] == space) {

      // string kembalian akan menjadi separator
      encrypted[i] = ' ';//unencrypted[i];
    } else {
      // konversi integer ke char menggunakan formula
      // E(n, key) = (n + key) % 26 sesuai jumlah abjad
      char ascii_list = (int)(unencrypted[i] + tokens - 97) % 26 + 97;
      encrypted[i] = ascii_list;
    }
  }
  return encrypted;

  // jangan lupa di free memory ygy
  // sebagai pencegahan dari memory leak
  free(encrypted);
}

int main(int argc, char *argv[]) {

  // passing argumen 1 untuk string
  // passing argumen 2 untuk token

  if (argc == 1) {

    // exit code 1 jika passing tidak berhasil
    // error handling sederhana untuk argumen
    printf("%s[!] Err%s, Not enough argument!\n", RED, WHITE);

    // exit(1) untuk failed
    exit(1);

    // mengecek kondisi apakah :
    // argument count > 1
    // argument 1 != NULL
    // argument 2 != NULL
  } else if ((argc > 1) && (argv[1] != NULL) && (argv[2] != NULL)) {

    int tokens = atoi(argv[2]); // string literal to integer

    // alokasi memori dengan ukuran sizeof(string)
    char *_return = malloc(sizeof(argv[1]));

    // fungsi encrypt!
    _return = encrypt(argv[1], tokens);
    printf("%s[!] Returning %s%s %sfrom %s%s\n\n", YELLOW, CYAN, _return, WHITE, CYAN,
           argv[1]);
    printf("%s • Status\t: %sOk\n", GREEN, CYAN);
    printf("%s • Origin\t: %s%s\n", GREEN, CYAN, argv[1]);
    printf("%s • Encrypted\t: %s%s\n\n", GREEN, CYAN, _return);

    // I/O File stream handler
    // digunakan untuk membuat log file
    FILE *fstream; // typedef fstream
    fstream = fopen("/data/data/com.termux/files/home/.csr_history",
                    "w"); // open file
    fprintf(fstream, ""); // print >> file
    fclose(fstream);      // fileclose

    // exit(0) untuk success
    free(_return);
    exit(0);
  } else if ((argc == 2) || (argv[2] == NULL)) {
    printf("%s[!] Err%s, keys cannot be NULL\n", RED, WHITE);
    exit(1);
  }
  return 0;
}
