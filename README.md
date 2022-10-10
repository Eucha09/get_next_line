# get_next_line

파일 디스크립터로부터 읽어 한 줄을 반환하는 함수 구현

## Mandatory part

| **함수 이름** | get_next_line |
| -- | ---- |
| **프로토타입** | char \*get_next_line(int fd); |
| **매개변수** | 읽어들일 파일의 디스크립터 (서술자) |
| **반환값** | 읽혀진 라인 : 한 줄이 제대로 읽힘 <br> NULL : 읽을 라인이 더이상 없거나 에러 발생 |
| **사용된 <br>외부 함수** | `read, malloc, free` |
| **설명** | 파일 디스크립터로부터 한 줄을 읽고, <br>반환하는 함수. |


**files**
- get_next_line.c
- get_next_line_utils.c
- get_next_line.h

## Bonus part

get_next_line을 사용하여 여러 개의 파일 디스크립터를 관리할 수 있게 구현. 예를 들어, 파일 디스크립터 3, 4, 5에 접근 가능한 경우, get_next_line은 각 디스크립터의 리딩 스레드를 잃지 않은 채로 3에서 한 번, 4에서 한 번, 다시 3에서 한 번, 5에서 한 번 호출될 수 있다.

**files**
- get_next_line_bonus.c
- get_next_line_utils_bonus.c
- get_next_line_bonus.h

## Example of execution

**a.txt**
```
a
a a
aa a

```

**b.txt**
```
b
b b

```

**c.txt**
```
c
c c
cc c
cc cc c

```

**main.c**
```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main()
{
	int fd[3];

	fd[0] = open("a.txt", O_RDONLY);
	fd[1] = open("b.txt", O_RDONLY);
	fd[2] = open("c.txt", O_RDONLY);

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			char *line = get_next_line(fd[j]);
			if(line != NULL)
				printf("%s", line);
			free(line);
		}
	}

	for(int i = 0; i < 3; i++)
		close(fd[i]);
	return 0;
}
```

**terminal**
```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c
./a.out
a
b
c
a a
b b
c c
aa a
cc c
cc cc c
```