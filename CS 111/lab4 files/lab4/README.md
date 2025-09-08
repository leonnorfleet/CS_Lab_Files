# Hey! I'm Filing Here

In this lab, I successfully implemented the following functions to create a functional
1MB ext2 file system with 2 directories, 1 regular file and 1 sym link:

```C
write_superblock
write_block_group_descriptor_table
write_block_bitmap
write_inode_bitmap
write_inode_table
write_root_dir_block
write_hello_world_file_block
```

By reading the comprehensive ext2 FS documentation, I was able to complete the data structures
required for the FS to successfully mount.

## Building

```console
make
```

## Running

```console
./ext2-create
mkdir mnt
sudo mount -o loop cs111-base.img mnt
```
The file system is now available in the mnt subdirectory

## Cleaning up

```console
sudo umount mnt
rmdir mnt
make clean
```

Make sure to leave the mnt directory before unmounting
