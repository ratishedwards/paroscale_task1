Write a library which maintains a Least Recently Used (LRU) cache for storing
information about files being opened by the applications. Information stored in the
cache could be : File path, timestamp at which it was opened, metadata information
of the file e.g size, timestamp, inode(Information returned by stat() system call)
The LRU cache should have a mechanism to remove the entries which have been
stored in the cache for a really long time.
Implement library calls to create LRU, add entry to LRU, search entry in LRU with
filepath as key, remove items from LRU
