# pam_printpw

Like the name suggest, pam_printpw is a very simple pam module that will print a
user username and password in a log file when the user attempt to login.

**Obviously this is very insecure, use at your own risk**

## Why?

I made this module check the username/password combination tried by bots
endlessly trying to bruteforce every ssh ports they can find on the internet.
But there are probably other fun ways to use it.

## Installation

This was only tested on Fedora 25 for now but it should be similar for other
linux distributions.

- Run ` make all ` to compile the module
- Copy the module `pam_printpw.so` to /lib64/security

To use the module with your ssh server add those two lines **at the top** of
`/etc/pam.d/sshd`:

```
auth       required     pam_unix.so
auth       required     pam_printpw.so
```

## Testing it

You shouldn't have to restart anything after the installation.

To test if it works, ssh to localhost (if you installed it locally) with `ssh youruser@127.0.0.1`

check the ssh logs to see if your username + password is there:
`journalctl -f -u sshd`

## Notes

- It will print the password regardless of if it's the good or wrong password
