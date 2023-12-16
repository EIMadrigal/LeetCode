```bash

```

`tr -s` deletes repetition of each char in SET1, then replaces each char of SET1 with corresponding char in SET2.

```bash
echo 'foosslinux' | tr -s 'SO' '_b'  # fb_linux
echo 'foosslinux' | tr -s 'SO'  # foslinux
```

`uniq -c` counts the number of previous duplicate lines.

```bash
## test.txt
# a
# a
# b
# a

uniq -c test.txt
# 2 a
# 1 b
# 1 a
```

