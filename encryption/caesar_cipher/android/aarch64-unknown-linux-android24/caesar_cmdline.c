/*
 * Implementasi Caesar Cipher di C
 * LLVM/CLANG versi 17.0.6
 * build aarch64-unknown-linux-android24
 * Lisensi : GNU General Public License 3
 */

#include <stdio.h>  // standar i/o stream
#include <stdlib.h> // standar alokasi memori ke char* / char[]
#include <string.h> // standar string utility

// text color
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define CYAN "\e[1;36m"
#define YELLOW "\e[1;33m"
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
      encrypted[i] = ' ';
    } else {
      // konversi integer ke char menggunakan formula
      // E(n, key) = (n + key) % 26 sesuai jumlah abjad
      char ascii_list = (int)(unencrypted[i] + tokens - 'a') % 26 + 'a';

      // bisa juga dengan
      // int ascii_int = (unencrypted[i] + tokens - 97) % 26 + 97;
      // encrypted[i] = (char) ascii_int;
      encrypted[i] = ascii_list;
    }
  }
  return encrypted;
}

/*
 * fungsi untuk mendeskripsi cipher text
 *
 */

char *decrypt(char *encrypted, int reverse) {

  char *unencrypted = malloc(sizeof(encrypted)); // alokasi memori

  // iterasi
  for (int i = 0; i < strlen(encrypted); i++) {

    // jika huruf ke i lebih besar / sama dengan 'a' atau 97
    // jika huruf ke i lebih kecil / sama dengam 'z' atau 123
    // percabangan menuju TRUE jika huruf kecil

    if ((encrypted[i] >= 'a') && (encrypted[i] <= 'z')) {

      // pos adalah posisi alphabet dalam digit
      int pos = encrypted[i] - 'a'; // a == 97 dalam ascii
      // new_pos = posisi baru jika sudah di shift
      int new_pos = (pos - reverse + 26) % 26;
      unencrypted[i] = 'a' + new_pos;

    } else {
      unencrypted[i] = encrypted[i];
    }
  }
  return unencrypted; // kembalian nilai untuk decrypt
}
// end function

int main(int argc, char *argv[]) {

  // passing argumen 1 untuk string
  // passing argumen 2 untuk token

  char *encode = "-e";

  if (argc == 1) {

    // exit code 1 jika passing tidak berhasil
    // error handling sederhana untuk argumen
    printf("%s[!] Err%s Not enough argument!\n", RED, WHITE);

    // exit(1) untuk failed
    exit(1);

    // mengecek kondisi apakah :
    // argument count > 1
    // argument 1 != NULL
    // argument 2 != NULL
  } else if ((argc == 3) && (argv[1] != NULL) && (argv[2] != NULL)) {

    int tokens = atoi(argv[2]); // string literal to integer

    // alokasi memori dengan ukuran sizeof(string)
    char *_return = malloc(sizeof(argv[1]));

    // fungsi encrypt!
    _return = encrypt(argv[1], tokens);
    printf("%s[!] Returning %s%s %sfrom %s%s\n\n", YELLOW, CYAN, _return, WHITE,
           CYAN, argv[1]);
    printf("%s • Status\t: %sOk\n", GREEN, CYAN);
    printf("%s • Origin\t: %s%s\n", GREEN, CYAN, argv[1]);
    printf("%s • Encrypted\t: %s%s\n", GREEN, CYAN, _return);
    printf("%s • Tokens\t: %s%s\n\n", GREEN, CYAN, argv[2]);
    free(_return);
    exit(0);
  } else if ((argc == 4) && (argv[1] != NULL) && (argv[2] != NULL) &&
             (strcmp(argv[3], encode) == 0)) {

    int reverse = atoi(argv[2]);

    char *unencrypted = malloc(sizeof(argv[1]));
    unencrypted = decrypt(argv[1], reverse);

    printf("%s[!] Returning %s%s %sfrom %s%s\n\n", YELLOW, CYAN, unencrypted,
           WHITE, CYAN, argv[1]);
    printf("%s • Status\t: %sOk\n", GREEN, CYAN);
    printf("%s • Encrypted\t: %s%s\n", GREEN, CYAN, argv[1]);
    printf("%s • Decrypted\t: %s%s\n", GREEN, CYAN, unencrypted);
    printf("%s • Tokens\t: %s%s\n\n", GREEN, CYAN, argv[2]);

  } else if ((argc == 2) || (argv[2] == NULL)) {
    printf("%s[!] Err%s keys cannot be NULL\n", RED, WHITE);
    exit(1);
  } else {
    exit(1);
  }
  return 0;
}
