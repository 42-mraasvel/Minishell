/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stat.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:26:21 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/10 21:23:13 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

/*
** Added ifdef macOS for some warnings
*/

#ifndef __APPLE__

void print_stat_linux(struct stat info) {
	printf("\n\t**INFO FILE STAT**\n\n");
	printf("%lu /* ID of device containing file */\n", info.st_dev);
	printf("%lu /* inode number */\n", info.st_ino);
	printf("%u /* Protection */\n", info.st_mode);
	printf("%lu /* number of hard links */\n", info.st_nlink);
	printf("%u /* user ID of owner */\n", info.st_uid);
	printf("%u /* group ID of owner */\n", info.st_gid);
	printf("%lu /* device ID (if special file) */\n", info.st_rdev);
	printf("%lu /* total size, in bytes */\n", info.st_size);
	printf("%lu /* blocksize for file system I/O */\n", info.st_blksize);
	printf("%lu /* number of 512B blocks allocated */\n", info.st_blocks);
	printf("%lu /* time of last access */\n", info.st_atime);
	printf("%lu /* time of last modification */\n", info.st_mtime);
	printf("%lu /* time of last status change */\n", info.st_ctime);
	printf("\n");
}

#else

void	print_stat_mac(struct stat info)
{
	printf("\n\t**INFO FILE STAT**\n\n");
	printf("%d /* ID of device containing file */\n", info.st_dev);
	printf("%llu /* inode number */\n", info.st_ino);
	printf("%u /* Protection */\n", info.st_mode);
	printf("%hu /* number of hard links */\n", info.st_nlink);
	printf("%u /* user ID of owner */\n", info.st_uid);
	printf("%u /* group ID of owner */\n", info.st_gid);
	printf("%d /* device ID (if special file) */\n", info.st_rdev);
	printf("%lld /* total size, in bytes */\n", info.st_size);
	printf("%d /* blocksize for file system I/O */\n", info.st_blksize);
	printf("%lld /* number of 512B blocks allocated */\n", info.st_blocks);
	printf("%lu /* time of last access */\n", info.st_atime);
	printf("%lu /* time of last modification */\n", info.st_mtime);
	printf("%lu /* time of last status change */\n", info.st_ctime);
	printf("\n");
}

#endif
