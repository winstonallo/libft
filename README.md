# LIBFT
When coding in C at 42 (which is most of our projects), we are only allowed basic functions/syscalls. 

Typically allowed standard library functions include: `malloc`, `free`, `open`, `close`, `read`, and `write`. The very first project of the curriculum, `libft` is about building your own library of utility functions. Back then, I was not very good at programming - my `printf` was writing byte by byte without any buffering, and I was not aware of data structures and their algorithms.

This repository is a collection of functions and data structures, partly optimized from my old `libft` (`ft_memset`, `ft_strlen`, ...), partly new ones I decided to build myself. The idea to make a `libft` on steroids was sparked by my attempt to write my own implementation of the `SHA256` cryptographic hash function, which made me feel miserable when compared to the `openssl` implementation. 

This collection now includes a hash map and a binary tree, which are additions I built (and will keep improving) out of pure interest for the way everyday data structures _actually_ work.
