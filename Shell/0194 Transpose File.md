```bash
# Read from the file file.txt and print its transposed content to stdout.
awk '{
    for (i = 1; i <= NF; i++) {
        if (NR == 1) {
            s[i] = $i
        } else {
            s[i] = s[i]" "$i
        }
    }
}
END {
    for (i in s) {
        print s[i]
    }
}' file.txt
```
