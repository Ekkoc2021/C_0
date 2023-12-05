# IO编程

1. **标准IO（缓冲IO）**： 标准IO是通过C语言的标准库函数（如stdio.h中的函数）来实现的，它提供了缓冲机制，可以提高IO性能。标准IO函数会在内存中设置缓冲区，将数据从文件系统读入缓冲区，然后通过函数调用将数据从缓冲区读取或写入。这些函数包括 `printf`、`scanf`、`fread`、`fwrite`等。标准IO适用于大多数情况，因为它们具有较好的性能，且易于使用。但是，标准IO可能会导致数据在缓冲区和文件系统之间的不一致，需要使用 `fflush`等函数进行同步。
2. **文件IO（原始IO或低级IO）**： 文件IO是直接通过系统调用来进行IO操作的，它提供了更直接的控制。文件IO函数包括 `open`、`read`、`write`、`close`等。文件IO不涉及缓冲区，数据会直接从文件系统读取到内存，或从内存写入到文件系统，因此更适用于对IO性能和精确控制要求较高的场景。但是，文件IO编程相对复杂，因为需要处理更多的细节，如数据的对齐、文件描述符管理等(实际的文件io也是有缓存的,不过是内核级别的缓存)

---

## 标准IO

缓冲类型

- 全缓冲==>没有空间了,填满了才进行新的io==>文件
- 行缓冲==>换行符号进行io,printf一定要加换行符号,终端
- 无缓冲==>不进行缓存

标准流

- 标准输入stdin
- 标准输出stdout
- 标准错误stderr

### 打开文件 `stdio.h`

```
FILE *fopen(const char *filename, const char *mode);
```

`const char *mode`：这是一个字符串，表示文件的打开模式。模式指定了您打开文件的目的，例如读取、写入、追加等。模式字符串可以包含以下标志的组合：

- `"r"`：只读模式。打开文件用于读取。文件必须存在，否则打开失败。
- `"w"`：写入模式。打开文件用于写入。如果文件存在，内容将被清除。如果文件不存在，将创建新文件。
- `"a"`：追加模式。打开文件用于写入，在文件末尾添加数据。如果文件不存在，将创建新文件。
- `"b"`：二进制模式。与其他模式一起使用，用于处理二进制文件。
- `"t"`：文本模式。与其他模式一起使用，用于处理文本文件（默认模式）。

`fopen` 函数成功打开文件时，将返回一个指向文件的文件流指针（`FILE *` 类型）。如果打开失败，它将返回 `NULL`。

 在大多数Unix-like操作系统中（例如Linux），新建文件的默认访问权限是由 "umask" 设置控制的。"umask" 是一个文件模式创建掩码，用于从新创建的文件权限中屏蔽某些位。这意味着新建文件的权限会受到 "umask" 的影响，以确保默认情况下文件不会具有过于宽松的权限。

 默认情况下，权限为 `0666`，而典型的 "umask" 值通常是 `022`，这会导致新建文件的权限为 `0644`(进行(&~操作)，文件io可以设置umask的值，设置为0则不会影响，默认权限，标准io中可以通过linux命令去修改。

### 关闭文件 `stdio.h`

```
int fclose(FILE *stream);
```

 `fclose` 函数成功关闭文件时返回 `0`，关闭失败时返回 `EOF`。

### 标准流读写 `stdio.h`

需要包含 `stdio.h`这个头文件

#### `fgetc` 函数：

- `int fgetc(FILE *stream);`
- 功能：从指定文件流中读取一个字符。
- 参数：文件流指针 `stream`，指向要读取的文件。
- 返回值：成功时返回读取的字符，到达文件末尾或出错时返回 `EOF`。

#### `fputc` 函数：

- `int fputc(int c, FILE *stream);`
- 功能：将一个字符 `c` 写入指定文件流。
- 参数：要写入的字符 `c`，文件流指针 `stream`。
- 返回值：成功时返回写入的字符，出错时返回 `EOF`。

#### `fgets` 函数：

- `char *fgets(char *str, int n, FILE *stream);`
- 功能：从指定文件流中读取一行数据，包括换行符。
- 参数：字符数组指针 `str`，最大字符数 `n`，文件流指针 `stream`。
- 返回值：成功时返回读取的字符串指针 `str`，到达文件末尾或出错时返回 `NULL`。

#### `fputs` 函数：

- `int fputs(const char *str, FILE *stream);`
- 功能：将一个以 null 结尾的字符串 `str` 写入指定文件流。
- 参数：要写入的字符串 `str`，文件流指针 `stream`。
- 返回值：成功时返回非负值，出错时返回 `EOF`。

#### `fread` 函数：

- `size_t fread(void *ptr, size_t size, size_t count, FILE *stream);`
- 功能：从指定文件流中读取数据到指定的内存缓冲区。
- 参数：内存缓冲区指针 `ptr`，每个元素的大小 `size`，要读取的元素数量 `count`，文件流指针 `stream`。
- 返回值：成功读取的元素数量，可能小于请求的数量

#### `fwrite` 函数：

- `size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);`
- 功能：将指定的内存缓冲区中的数据写入到指定文件流。
- 参数：内存缓冲区指针 `ptr`，每个元素的大小 `size`，要写入的元素数量 `count`，文件流指针 `stream`。
- 返回值：成功写入的元素数量，可能小于请求的数量

### 流的刷新 `stdio.h`

- 缓冲区满
- 关闭流
- fflush函数主动刷新

  ```
  int fflush(FILE *stream);
  ```

### 流的定位 `stdio.h`

#### `ftell` 函数：

- `long ftell(FILE *stream);`
- 功能：返回当前文件流的位置（偏移量），即当前读/写的字节数。
- 参数：文件流指针 `stream`。
- 返回值：当前位置的偏移量，出错时返回 `−1L`

#### `fseek` 函数：

- `int fseek(FILE *stream, long offset, int whence);`
- 功能：设置文件流的位置（偏移量）。
- 参数：文件流指针 `stream`，偏移量 `offset`，基准点 `whence`（`SEEK_SET`、`SEEK_CUR`、`SEEK_END`）。
- 返回值：成功时返回 `0`，出错时返回非零值。

#### `rewind` 函数：

- `void rewind(FILE *stream);`
- 功能：将文件流的位置重置到文件开头。
- 参数：文件流指针 `stream`。

### 检查流 `stdio.h`

#### `ferror` 函数：

- `int ferror(FILE *stream);`
- 功能：检查文件流是否在之前的IO操作中发生了错误。
- 参数：文件流指针 `stream`。
- 返回值：如果之前的IO操作发生错误，返回非零值（通常为1），否则返回0

#### `feof` 函数：

- `int feof(FILE *stream);`
- 功能：检查文件流是否已经到达文件末尾。
- 参数：文件流指针 `stream`。
- 返回值：如果文件流已到达末尾，返回非零值（通常为1），否则返回0。

### 格式化输入输出`stdio.h`

#### `printf` 函数：

- `int printf(const char *format, ...);`
- 功能：将格式化的数据输出到标准输出（通常是控制台）。
- 参数：格式化字符串 `format`，可变数量的参数，根据格式字符串的指定来进行输出。
- 返回值：成功时返回输出的字符数，出错时返回负值。

#### `sprintf` 函数：

- `int sprintf(char *str, const char *format, ...);`
- 功能：将格式化的数据写入指定的字符数组缓冲区。
- 参数：字符数组指针 `str`，格式化字符串 `format`，可变数量的参数。
- 返回值：成功时返回输出的字符数，出错时返回负值。

#### `fprintf` 函数：

- `int fprintf(FILE *stream, const char *format, ...);`
- 功能：将格式化的数据输出到指定文件流。
- 参数：文件流指针 `stream`，格式化字符串 `format`，可变数量的参数。
- 返回值：成功时返回输出的字符数，出错时返回负值。

#### `fscanf` 函数

- `int fscanf(FILE *stream, const char *format, ...);`
- 功能： `fscanf` 函数用于从文件流中按照指定的格式读取数据。
- 参数：`stream`：文件流指针，指向要读取数据的文件。`format`：格式化字符串，指定了数据的格式和读取方式。`...`：可变数量的参数，对应于格式化字符串中的格式指示符。
- 返回值：`fscanf` 函数在成功读取数据时返回成功匹配的参数数量，如果无法匹配或出错，返回值可能小于预期的参数数量，或者返回 `EOF`。

---

## 文件IO

- 遵循posix标准
- 无缓冲==>每次都有系统调用
- 文件描述符==>不是流
- 访问各种文件类型(linux:everything is file)

文件描述符

- 非负整数
- 从0开始,依次递增(程序之间隔离,单独的,不是整个系统)
- 0,1,2含义==>标准输入,标准输出,标准错误

### 打开文件 `fcntl.h`

#### `open`函数

open函数包含在 `fcntl.h`头文件中

函数原型：

```c
int open(const char *pathname, int flags, mode_t mode);
```

- `pathname`：要打开或创建的文件的路径。
- `flags`：打开文件的标志，如 `O_RDONLY`（只读）、`O_WRONLY`（只写）、`O_RDWR`（读写）等。还可以通过位运算设置其他标志，例如 `O_CREAT`（如果文件不存在则创建）、`O_APPEND`（在文件末尾追加）、`O_TRUNC`（清空文件内容）等。可以用 `|`运算连接表示功能叠加
- `mode`：创建新文件时的权限（仅在 `O_CREAT` 标志被设置时有效）。通常使用八进制表示，如 `0644`。

返回值：

- 成功时，返回一个非负整数，表示文件描述符（file descriptor）。文件描述符是一个与文件相关联的整数，可以在后续的文件操作中使用。
- 失败时，返回 -1，并设置全局变量 `errno` 表示错误类型。

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (fd != -1) {
        write(fd, "Hello, world!", 13);
        close(fd);
    } else {
        perror("Failed to open or create the file");
    }
    return 0;
}
```

### 关闭文件 `unistd.h`

#### `close` 函数

`close` 函数用于关闭文件描述符，释放操作系统资源，并将文件描述符从进程的文件表中移除。在C语言中，它是在 `unistd.h` 头文件中声明的函数。

函数原型：

```
int close(int fd);
```

- `fd`：要关闭的文件描述符。

返回值：

- 成功时，返回 0。
- 失败时，返回 -1，并设置全局变量 `errno` 表示错误类型

### 读写位置设置 `unistd.h`

#### `lseek()`函数

`lseek()` 是UNIX和类UNIX操作系统中的一个系统调用，用于在打开的文件中移动文件指针（读写位置）。通过调用 `lseek()` 函数，您可以在文件中定位到指定的偏移量位置，以便在接下来的读取或写入操作中进行操作。

`lseek()` 函数的原型如下：

```c
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```

其中：

- `fd` 是文件描述符，用于指定要进行操作的文件。
- `offset` 是相对于 `whence` 的偏移量。这是一个长整型值，表示要移动的字节数。
- `whence`是基准位置，可能的值有：
  - `SEEK_SET`：从文件开头开始计算偏移量。
  - `SEEK_CUR`：从当前文件指针位置开始计算偏移量。
  - `SEEK_END`：从文件末尾开始计算偏移量。

`lseek()` 函数返回新的文件指针位置（偏移量），如果操作失败，则返回 `-1`。

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("无法打开文件");
        return 1;
    }

    off_t offset = lseek(fd, 0, SEEK_END);  // 移动到文件末尾
    if (offset == -1) {
        perror("无法定位文件末尾");
        close(fd);
        return 1;
    }

    printf("文件末尾位置：%ld\n", (long)offset);

    close(fd);

    return 0;
}
```

### 读写刷新`unistd.h`

#### `read` 函数

`read()` 是一个系统调用函数，用于从文件描述符中读取数据。这个函数通常用于从**打开的文件、管道、套接字**等中读取数据。在C语言中，`read()` 函数位于 `unistd.h` 头文件中。

`read()` 函数的原型如下：

```
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

其中：

- `fd` 是文件描述符，指定要从哪个文件或资源读取数据。
- `buf` 是指向用于存储读取数据的缓冲区的指针。
- `count` 是要读取的最大字节数。

`read()` 函数返回实际读取的字节数。如果返回值是0，表示已达到文件末尾。如果返回值是-1，表示发生错误。

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("无法打开文件");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("读取文件时发生错误");
        close(fd);
        return 1;
    }

    printf("读取到的数据：%.*s\n", (int)bytesRead, buffer);

    close(fd);

    return 0;
}
```

#### `write` 函数

`write()` 是一个系统调用函数，用于将数据写入文件描述符中，比如打开的文件、管道、套接字等。在C语言中，`write()` 函数位于 `unistd.h` 头文件中。

`write()` 函数的原型如下：

```
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

其中：

- `fd` 是文件描述符，指定要向哪个文件或资源写入数据。
- `buf` 是一个指向包含要写入数据的缓冲区的指针。
- `count` 是要写入的字节数。

`write()` 函数返回实际写入的字节数。如果返回值是-1，表示写入过程中发生错误。

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);

    if (fd == -1) {
        perror("无法打开文件");
        return 1;
    }

    const char *data = "这是要写入的数据。\n";
    ssize_t bytesWritten = write(fd, data, strlen(data));

    if (bytesWritten == -1) {
        perror("写入文件时发生错误");
        close(fd);
        return 1;
    }

    printf("成功写入 %zd 字节\n", bytesWritten);

    close(fd);

    return 0;
}
```

#### `fsync` 函数

`fsync` 函数的函数原型如下：

```
#include <unistd.h>

int fsync(int fd);
```

参数和返回值说明如下：

- `fd`：是一个文件描述符，它指定要刷新的文件。这个文件描述符必须是已经打开的文件。
- 返回值：如果 `fsync` 调用成功，它将返回0；如果出现错误，它将返回-1，并设置全局变量 `errno` 来指示错误的类型。

 `fsync` 的主要目的是确保指定文件的数据和元数据被写入磁盘，以保持数据的持久性。如果调用成功，它表示数据已经被成功刷新到磁盘上，这在需要强一致性的文件操作中非常有用，例如在写入数据库日志文件时。但请注意，由于等待磁盘写入完成可能引起性能开销，所以在一些情况下需要权衡性能和数据一致性。 

---



### 目录操作 `dirent.h`

 `dirent.h` 是一个C语言标准库中的头文件，通常在UNIX和类UNIX操作系统中使用。它提供了操作目录及其内容的函数和数据结构。通过使用 `dirent.h` 头文件中定义的函数，您可以获取目录中的文件列表、文件属性等信息。

**数据结构**：

1. `struct dirent`：表示目录中的一个项。包括文件名和文件类型等信息。

```c
struct dirent {
    ino_t d_ino;         // inode号
    off_t d_off;         // 在目录文件中的偏移量
    unsigned short d_reclen;  // 记录长度
    unsigned char d_type;     // 文件类型
    char d_name[];       // 文件名
};
```

**函数**：(常用就是opendir,readdir,closedir)

1. `DIR *opendir(const char *name);`
- 打开指定名称的目录，并返回一个指向 `DIR` 结构的指针。
   - `name` 是目录的路径。
2. `struct dirent *readdir(DIR *dirp);`
- 从目录流中读取下一个目录项，返回一个指向 `struct dirent` 结构的指针。
   - `dirp` 是由 `opendir()` 返回的目录指针。
3. `int closedir(DIR *dirp);`
- 关闭由 `opendir()` 打开的目录。
   - `dirp` 是要关闭的目录指针。
4. `void rewinddir(DIR *dirp);`

   - 重置由 `opendir()` 打开的目录流，将文件指针重置到目录的起始位置。
   - `dirp` 是要重置的目录指针。
5. `struct dirent *readdir(DIR *dirp); `

- `dirp` 是由 `opendir()` 打开的目录指针。
- `readdir()` 函数返回一个指向 `struct dirent` 结构的指针，如果读取到了目录的末尾或发生错误，返回 `NULL`。

```c
   #include <stdio.h>
   #include <dirent.h>
   
   int main() {
       const char *dirPath = ".";  // 当前目录
   
       DIR *dir = opendir(dirPath);
       if (dir == NULL) {
           perror("无法打开目录");
           return 1;
       }
   
       struct dirent *entry;
       while ((entry = readdir(dir)) != NULL) {
           printf("文件名: %s\n", entry->d_name);
       }
   
       closedir(dir);
   
       return 0;
   }
```

### 权限修改 `sys/stat.h`

权限相关的宏

```
S_IRUSR：用户（文件所有者）的读权限。
S_IWUSR：用户的写权限。
S_IXUSR：用户的执行权限。
S_IRGRP：所属组的读权限。
S_IWGRP：所属组的写权限。
S_IXGRP：所属组的执行权限。
S_IROTH：其他用户的读权限。
S_IWOTH：其他用户的写权限。
S_IXOTH：其他用户的执行权限。
```

#### `chmod` 函数

默认的文件权限会与umask进行操作,可以自己修改文件权限

`chmod` 是一个用于改变文件或目录权限的UNIX命令，也可以在C语言中使用 `chmod()` 函数进行相同的操作。这个操作可以更改文件或目录的读、写和执行权限，以及文件的所有者和所属组。

在C语言中，`chmod()` 函数位于 `sys/stat.h` 头文件中，用于更改文件或目录的权限。

```
#include <sys/stat.h>

int chmod(const char *pathname, mode_t mode);
```

- `pathname` 是要更改权限的文件或目录的路径。
- `mode` 是权限模式，以八进制表示。通常使用的模式位是 `S_IRUSR`、`S_IWUSR`、`S_IXUSR` 等。

 `chmod()` 函数返回 `0` 表示成功，返回 `-1` 表示出错。

```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filePath = "example.txt";
    mode_t newMode = S_IRUSR | S_IWUSR;  // 新的权限模式（读写权限）

    if (chmod(filePath, newMode) == -1) {
        perror("更改权限时发生错误");
        return 1;
    }

    printf("权限已成功更改\n");

    return 0;
}
//我们使用 chmod() 函数将指定文件的权限更改为只读和可写权限。S_IRUSR 表示用户（文件所有者）的读权限，S_IWUSR 表示用户的写权限。更多权限位可以在 sys/stat.h 头文件中找到。
```

#### `fchmod` 函数

`fchmod` 是一个函数，用于改变已打开文件的权限。在C语言中，`fchmod()` 函数位于 `sys/stat.h` 头文件中，用于更改文件的权限。与 `chmod()` 函数不同，`fchmod()` 函数不需要文件的路径，而是直接操作已打开的文件描述符。

```
#include <sys/stat.h>

int fchmod(int fd, mode_t mode)
```

- `fd` 是已打开文件的文件描述符。
- `mode` 是权限模式，以八进制表示。通常使用的模式位是 `S_IRUSR`、`S_IWUSR`、`S_IXUSR` 等。

 `fchmod()` 函数返回 `0` 表示成功，返回 `-1` 表示出错。

```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filePath = "example.txt";
    mode_t newMode = S_IRUSR | S_IWUSR;  // 新的权限模式（读写权限）

    int fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        perror("无法打开文件");
        return 1;
    }

    if (fchmod(fd, newMode) == -1) {
        perror("更改权限时发生错误");
        close(fd);
        return 1;
    }

    printf("权限已成功更改\n");

    close(fd);

    return 0;
}
```

### 文件信息 `sys/stat.h`

`sys/stat.h`:获取文件信息相关功能

文件信息结构体

```
struct stat {

        mode_t     st_mode;       //文件对应的模式，文件，目录等
        ino_t      st_ino;       //inode节点号
        dev_t      st_dev;        //设备号码
        dev_t      st_rdev;       //特殊设备号码
        nlink_t    st_nlink;      //文件的连接数
        uid_t      st_uid;        //文件所有者
        gid_t      st_gid;        //文件所有者对应的组
        off_t      st_size;       //普通文件，对应的文件字节数
        time_t     st_atime;      //文件最后被访问的时间
        time_t     st_mtime;      //文件内容最后被修改的时间
        time_t     st_ctime;      //文件状态改变时间
        blksize_t st_blksize;    //文件内容对应的块大小
        blkcnt_t   st_blocks;     //伟建内容对应的块数量
      };

```

文件类型st_mode

```
文件类型位字段的S_IFMT 0170000 位掩码
S_IFSOCK 0140000 套接字
S_IFLNK 0120000 符号链接
S_IFREG 0100000 常规文件
S_IFBLK 0060000 块设备
S_IFDIR 0040000 目录
S_IFCHR 0020000 字符设备
S_IFIFO 0010000 先进先出
设置UID位S_ISUID 0004000
S_ISGID 0002000 集组id位(见下)
S_ISVTX 0001000 粘性位(见下)
S_IRWXU 00700 文件所有者权限掩码
```

可以用相关宏来判断st_mode

```
S_ISREG(m) 是常规文件吗?
S_ISDIR (m) 目录吗?
S_ISCHR (m) 字符设备?
S_ISBLK (m) 块设备?
S_ISFIFO(m)  FIFO(命名管道)?
S_ISLNK (m) 符号链接呢? (不是posix . 1的授权- 1996)。
S_ISSOCK (m) 套接字? (不是posix . 1的授权- 1996)。
```

st_mode的位结构

```
| 15  14  13  12 | 11  10  9 | 8  7  6    | 5  4  3    | 2  1  0 |
| -------------- | --------- | ---------- | ---------- | ------- |
| File Type      | User Mode | Group Mode | Other Mode |         |
```

文件类型（位 12-15）：这四个位表示文件的类型。下面是一些常见的文件类型和对应的值：

- 普通文件：`1000`
- 目录：`1010`
- 符号链接：`1110`
- 字符设备：`1100`
- 块设备：`1101`
- 套接字：`1100`
- 命名管道：`1111`

用户模式（位 9-11）：这三个位表示文件所有者的权限。

组模式（位 6-8）：这三个位表示文件所属组的权限。

其他模式（位 3-5）：这三个位表示其他用户的权限。

每个模式中的权限位使用以下的三位二进制表示：

- 读权限：`100` 或 `r`。
- 写权限：`010` 或 `w`。
- 执行权限：`001` 或 `x`。

例如，`rwxr-xr--` 表示文件所有者具有读、写和执行权限，所属组具有读和执行权限，其他用户只有读权限。

结合已定义的宏解析mode:

```c
void print_permissions(mode_t mode) {
    printf("权限：");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}
```

#### `stat` 函数

`stat` 是一个UNIX命令，用于获取文件或目录的详细信息，包括文件类型、权限、所有者、大小、时间戳等。在C语言中，可以使用 `stat()` 函数来实现相同的操作。`stat()` 函数位于 `sys/stat.h` 头文件中，用于获取指定文件的元数据信息。

```
#include <sys/stat.h>

int stat(const char *pathname, struct stat *statbuf);
```

- `pathname` 是要获取信息的文件或目录的路径。
- `statbuf` 是一个指向 `struct stat` 结构的指针，用于存储文件的元数据信息。

`stat()` 函数返回 `0` 表示成功，返回 `-1` 表示出错。

#### `lstat`函数

`lstat` 是一个UNIX命令，用于获取文件或符号链接的详细信息，但不会跟随符号链接指向的实际文件。在C语言中，可以使用 `lstat()` 函数来实现相同的操作。`lstat()` 函数位于 `sys/stat.h` 头文件中，用于获取指定文件的元数据信息，类似于 `stat()` 函数。

与 `stat()` 函数不同，`lstat()` 函数不会跟随符号链接指向的实际文件，而是获取符号链接本身的信息。

使用 `lstat()` 函数需要对指定的文件或符号链接有足够的权限。只有文件的所有者、所属组以及超级用户（root）通常可以获取文件的元数据信息。

```c
#include <sys/stat.h>

int lstat(const char *pathname, struct stat *statbuf);
```

- `pathname` 是要获取信息的文件或符号链接的路径。
- `statbuf` 是一个指向 `struct stat` 结构的指针，用于存储文件的元数据信息。

`lstat()` 函数返回 `0` 表示成功，返回 `-1` 表示出错。

#### `fstat`函数

 `fstat` 是一个UNIX命令，用于获取已打开文件的详细信息。在C语言中，可以使用 `fstat()` 函数来实现相同的操作。`fstat()` 函数位于 `sys/stat.h` 头文件中，用于获取已打开文件的元数据信息。

```
#include <sys/stat.h>

int fstat(int fd, struct stat *statbuf);
```

- `fd` 是已打开文件的文件描述符。
- `statbuf` 是一个指向 `struct stat` 结构的指针，用于存储文件的元数据信息。

`fstat()` 函数返回 `0` 表示成功，返回 `-1` 表示出错。





## 自定义库

### 静态库制作

 静态库的主要特点是编译时静态链接，这意味着库的代码会被复制到最终的可执行文件中。当你构建一个使用了静态库的程序时，编译器会将库中的代码与你的程序代码合并，生成一个独立的可执行文件，其中包含了所有需要的代码。

1. **编写代码并编译成对象文件：** 首先，你需要编写库的代码，并将其编译成对象文件（`.o` 文件）。这可以通过单独的编译步骤完成，例如：

   ```
   gcc -c mylib.c -o mylib.o
   ```
2. **创建静态库：** 接下来，你可以使用工具来将多个对象文件打包成一个静态库文件（`.a` 文件）：

   ```
   ar rcs libmylib.a mylib.o
   ```

   这将创建一个名为 `libmylib.a` 的静态库文件，其中包含了 `mylib.o` 的代码。
3. 编译并链接静态库

   ```
   gcc myprogram.c -o myprogram -L. -lmylib
   ```

   `-L.` 表示告诉编译器在当前目录中搜索库文件。具体来说，`-L` 选项用于指定库文件搜索路径，而 `.` 表示当前目录。
   `-lmylib` 表示要链接名为 `mylib` 的库。编译器将会搜索以 `lib` 开头、以 `.a`（静态库）或 `.so`（共享库） 结尾的文件，并尝试将其链接到生成的可执行文件中。

### 动态库(共享库)制作

动态链接库（Dynamic Link Library，DLL，在Windows环境中常用），是一种在运行时被动态加载到应用程序中的代码库。与静态库不同，共享库的代码不会被复制到最终的可执行文件中，而是在运行时由操作系统动态加载。

共享库的主要特点是在运行时动态链接，这意味着共享库的代码不会被嵌入到应用程序中，而是保留在独立的文件中。应用程序在运行时通过操作系统来加载和链接共享库，这样多个应用程序可以共享同一个库的实例，从而减少内存占用，并使库的更新更加方便。

优点

- 节省内存
- 更新灵活
- 运行时链接
- 独立
- 可执行文件更小
- 多版本共存

 运行时需要进行动态链接，可能会导致稍微降低一些性能，因为需要在运行时进行加载和链接。此外，管理共享库的依赖关系、版本控制和兼容性也需要一些注意。

制作流程

1. **编译共享库**

   ```
   gcc -c -fPIC mylib1.c mylib2.c -Wall
   ```

   - `-c` 表示只进行编译而不进行链接
   - `-fPIC` 表示生成位置无关代码（Position Independent Code） 这是为了在后续创建共享库时使用，因为共享库需要在不同的内存位置加载，所以使用位置无关代码可以避免地址相关的问题。(有这个参数能真正达到代码共享)
   - `-Wall` 启用了编译器的警告提示。
2. **创建共享库：** 接下来，你可以将多个对象文件编译成共享库文件（`.so` 文件或 `.dll` 文件，具体格式取决于操作系统）：

   ```
   gcc -shared -o libmylib.so mylib1.o mylib2.o
   ```

   这将创建一个名为 `libmylib.so` 的共享库文件。

   版本控制

   ```
   gcc -shared -Wl,-soname,libtest.so -o libtest.so.0.0.0 test.o
   # 创建了一个共享库,真实名称:libtest.so.0.0.0,别名libtest.so
   # 可以直接直接通-ltest找到实际的共享库

   #------------------------------

   gcc -shared -o libtest.so.0.0.0 test.o
   # 需要一个连接将libtest.so指向真实库,才能直接使用-ltest
   ln -s libtest.so.0.0.0 libtest.so

   #----
   控制版本最终都需要源文件重新编译,重新编译设置soname 和新的库文件名称需要和旧版本的不一致,至于不影响使用旧版本的程序正常使用

   通常情况 ln指定一个固定的软连接 指向soname,n的文件名称不变,编译使用make文件不变,更新只要修改soname和真实名称即可,重新编译即可
   ```
3. **编译并链接程序：** 编译并链接你的程序时，需要指定要链接的共享库：

   ```
   gcc myprogram.c -o myprogram -L. -lmylib
   ```

   这会在运行时动态加载和链接 `libmylib.so` 共享库。

**路径问题**

对于动态库（共享库）来说，即使你在当前目录中有共享库文件，操作系统在默认情况下可能不会直接在当前目录中查找共享库。这是为了安全性考虑，避免意外或恶意的库被加载。 需要设置 `LD_LIBRARY_PATH` 环境变量，或者将共享库的路径添加到 `/etc/ld.so.conf` 文件中，然后运行 `ldconfig` 命令更新共享库的缓存。

```
ldconfig -v
# 查看当前系统库位置,编译器自动在这些位置进行连接库
```

1. **临时设置：** 如果你只想在当前会话中设置 `LD_LIBRARY_PATH`，可以在终端中运行以下命令：

   ```
   shellCopy codeexport LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
   ```

   这将将当前目录 `.` 添加到 `LD_LIBRARY_PATH` 变量中，使系统在查找动态库时也搜索当前目录。
2. **永久设置1：** 如果你希望在每次登录时都自动设置 `LD_LIBRARY_PATH`，可以将上述命令添加到你的 shell 配置文件中，例如 `~/.bashrc`（如果你使用 Bash shell）：

   ```
   shellCopy codeecho 'export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH' >> ~/.bashrc
   source ~/.bashrc
   ```

   这样，每次登录时都会自动设置 `LD_LIBRARY_PATH`。
3. **永久设置2：** `/etc/ld.so.conf.d/` 目录用于存放系统库加载时的配置文件。在 Linux 系统中，库加载器使用这些配置文件来确定库的搜索路径。每个配置文件对应一个目录，指定了库加载器在运行时查找共享库时应该搜索的路径。
   在这个目录创建一个配置文件

```
   sudo nano /etc/ld.so.conf.d/my_library.conf
```

   写入路径:.表示当前编译命令所在路径

```
   .
```

   重载配置

```
   sudo ldconfig
```

### 库的选择

如果共享和静态同时存在优先使用共享库

可以指定强制使用静态库

```
# 使用共享库
gcc main.c -o myprogram -L. -lmylib

# 使用静态库（添加 -static 参数）
gcc main.c -o myprogram -L. -lmylib -static
```

---

## 错误信息处理 `errno.h`

在 `errno.h`这个头文件中定义了处理错误的功能

在使用 `errno` 时，通常的做法是：

1. 调用可能会设置 `errno` 的函数。
2. 检查 `errno` 的值来判断是否有错误发生。
3. 根据需要使用 `perror` 或 `strerror` 函数来输出错误信息。

引入这个头文件后每个进程都会维护一个 `errno`,用于记录当前发生的可记录错误的编号,可以通过这个编号输出这个错误信息

1. **`errno` 变量：**
   - `errno` 是一个整数变量，通常声明为 `extern int errno;`。它在错误发生时被标准库函数或系统调用设置为相应的错误代码。
2. **错误代码：**
   - `errno` 的值可能是不同的错误代码。这些错误代码在不同的系统和编译器中可能会有所不同，但一些常见的错误代码包括：
     - `EACCES`：权限不足（拒绝访问）。
     - `EINVAL`：无效参数。
     - `ENOENT`：文件或路径不存在。
     - `ENOMEM`：内存不足。
     - `EIO`：输入/输出错误。
     - 等等...
3. **`perror` 函数：**
   - `perror` 是一个函数，用于将 `errno` 对应的错误信息输出到标准错误流（通常是终端屏幕）。
   - 示例用法：`perror("File not found");`
4. **`strerror` 函数：**
   - `strerror` 是一个函数，接受一个错误代码作为参数，返回对应的错误描述字符串。
   - 示例用法：`printf("Error: %s\n", strerror(errno));`

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistent_file.txt", "r");
    if (file == NULL) {
        perror("Error opening file"); //错误会用:拼接在传入参数后
        printf("Error code: %d\n", errno);
        printf("Error description: %s\n", strerror(errno));
    }
	// 可以自己清除errno的值
    return 0;
}
```

---

## 时间库 `time.h`

1. **`time_t`：**
   - `time_t` 是一个整数类型，在C中用于表示从"纪元"（通常是1970年1月1日UTC）到当前时间的秒数。
2. **`struct tm` 结构体：**
   - `struct tm` 表示了日期和时间的分解格式，包括年、月、日、时、分、秒等信息。
3. **`time` 函数：**
   - `time_t time(time_t *timer);`
   - 获取当前时间，并以 `time_t` 格式返回。不需要存放传入参数NULL即可,返回值有
4. **`gmtime` 函数：**
   - `struct tm *gmtime(const time_t *timer);`
   - 将 `time_t` 格式的时间转换为 `struct tm` 格式的协调世界时（UTC）时间。
5. **`localtime` 函数：**
   - `struct tm *localtime(const time_t *timer);`
   - 将 `time_t` 格式的时间转换为 `struct tm` 格式的本地时间。
6. **`strftime` 函数：**
   - `size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr);`
   - 将 `struct tm` 格式的时间按照指定的格式化字符串输出到字符数组中。
7. **`asctime` 函数：**
   - `char *asctime(const struct tm *timeptr);`
   - 将 `struct tm` 格式的时间转换为字符串形式。
8. **`difftime` 函数：**
   - `double difftime(time_t time1, time_t time0);`
   - 计算两个 `time_t` 时间之间的差值，以秒为单位。

```c
#include <time.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{

    time_t now;
    now = time(NULL);
    struct tm *nowDate = localtime(&now);
    printf("year: %d \n", nowDate->tm_year + 1900);
    printf("Month: %d\n", nowDate->tm_mon + 1);
    printf("Day: %d\n", nowDate->tm_mday);
    printf("Hour: %d\n", nowDate->tm_hour);
    printf("Minute: %d\n", nowDate->tm_min);
    printf("Second: %d\n", nowDate->tm_sec);
    return 0;
}
```

## 系统相关的功能库  `unistd.h`

 `unistd.h` 是C语言标准库的一个头文件，提供了许多与操作系统相关的功能，特别是在Unix-like系统中。它包含了许多系统调用和常量，用于处理文件、进程、系统信息等。

如:

**系统调用**：

- `read`：`ssize_t read(int fd, void *buf, size_t count);`
  - 参数：`fd` 是文件描述符，`buf` 是读取数据的缓冲区，`count` 是要读取的字节数。
  - 返回值：读取的字节数，或者错误时返回 -1。
  - 功能：从文件描述符中读取数据。
- `write`：`ssize_t write(int fd, const void *buf, size_t count);`
  - 参数：`fd` 是文件描述符，`buf` 是要写入的数据缓冲区，`count` 是要写入的字节数。
  - 返回值：写入的字节数，或者错误时返回 -1。
  - 功能：向文件描述符中写入数据。
- `close`：`int close(int fd);`
  - 参数：`fd` 是要关闭的文件描述符。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：关闭文件描述符。
- `fork`：`pid_t fork(void);`
  - 参数：无参数。
  - 返回值：在父进程中返回子进程的进程ID，在子进程中返回 0，失败时返回 -1。
  - 功能：创建一个新的进程，其中子进程是父进程的副本。
- `exec`：这是一组函数（如 `execl`, `execv`, `execle` 等）用于在当前进程中执行新的程序。
  - 参数：取决于不同的 `exec` 函数。
  - 返回值：只有在发生错误时返回 -1，成功时不返回。
  - 功能：用新的程序替换当前进程，用新的代码和数据加载程序。
- `pipe`：`int pipe(int pipefd[2]);`
  - 参数：`pipefd` 是一个整数数组，包含两个文件描述符，一个用于读取，一个用于写入。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：创建一个管道，用于进程间通信。

**文件操作：**

- `access`：`int access(const char *pathname, int mode);`
  - 参数：`pathname` 是文件路径，`mode` 是要检查的访问模式（例如 `F_OK` 表示检查文件是否存在）。
  - 返回值：0 表示成功（文件存在或具有所需权限），-1 表示错误。
  - 功能：检查文件是否可访问。
- `unlink`：`int unlink(const char *pathname);`
  - 参数：`pathname` 是要删除的文件路径。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：删除一个文件。
- `rename`：`int rename(const char *oldpath, const char *newpath);`
  - 参数：`oldpath` 是原文件路径，`newpath` 是新文件路径。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：重命名文件。
- `truncate`：`int truncate(const char *path, off_t length);`
  - 参数：`path` 是文件路径，`length` 是截断后的文件长度。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：将文件截断为指定的长度。

**目录操作：**

- `chdir`：`int chdir(const char *path);`
  - 参数：`path` 是目标工作目录的路径。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：改变当前工作目录。
- `getcwd`：`char *getcwd(char *buf, size_t size);`
  - 参数：`buf` 是接收当前工作目录的缓冲区，`size` 是缓冲区大小。
  - 返回值：返回 `buf`，或者 NULL 表示错误。
  - 功能：获取当前工作目录。
- `mkdir`：`int mkdir(const char *pathname, mode_t mode);`
  - 参数：`pathname` 是要创建的目录路径，`mode` 是目录的权限。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：创建一个目录。
- `rmdir`：`int rmdir(const char *pathname);`
  - 参数：`pathname` 是要删除的目录路径。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：删除一个目录。

**进程控制：**

- `getpid`：`pid_t getpid(void);`
  - 参数：无参数。
  - 返回值：当前进程的进程ID。
  - 功能：获取当前进程的进程ID。
- `getppid`：`pid_t getppid(void);`
  - 参数：无参数。
  - 返回值：父进程的进程ID。
  - 功能：获取父进程的进程ID。
- `getuid`：`uid_t getuid(void);`
  - 参数：无参数。
  - 返回值：当前用户的用户ID。
  - 功能：获取用户ID。
- `getgid`：`gid_t getgid(void);`
  - 参数：无参数。
  - 返回值：当前用户的组ID。
  - 功能：获取组ID。
- `setuid`：`int setuid(uid_t uid);`
  - 参数：`uid` 是要设置的用户ID。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：设置用户ID。

**系统信息：**

- `sleep`：`unsigned int sleep(unsigned int seconds);`
  - 参数：`seconds` 是要睡眠的秒数。
  - 返回值：返回未睡眠的剩余秒数。
  - 功能：使程序睡眠指定的秒数。
- `usleep`：`int usleep(useconds_t usec);`
  - 参数：`usec` 是要睡眠的微秒数。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：使程序睡眠指定的微秒数。
- `gethostname`：`int gethostname(char *name, size_t len);`
  - 参数：`name` 是接收主机名的缓冲区，`len` 是缓冲区大小。
  - 返回值：0 表示成功，-1 表示错误。
  - 功能：获取主机名。
- `getpagesize`：`int getpagesize(void);`
  - 参数：无参数。
  - 返回值：页面大小（字节）。
  - 功能：获取系统的页面大小。

**其他：**

- `isatty`：`int isatty(int fd);`
  - 参数：`fd` 是文件描述符。
  - 返回值：如果文件描述符关联到终端，则返回 1，否则返回 0。
  - 功能：检查文件描述符是否为终端。
- `pathconf`：`long pathconf(const char *path, int name);`
  - 参数：`path` 是文件或目录的路径，`name` 是要查询的配置值。
  - 返回值：指定配置值，或者 -1 表示错误。
  - 功能：获取文件或目录的配置值。
