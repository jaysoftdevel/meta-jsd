#!/bin/sh

HTPASSWD_FILE="/etc/apache2/.htpasswd"
HTUSER="done"
PASS="funk"

if [ ! -f "${HTPASSWD_FILE}" ]; then
    echo "Creating .htpasswd for ${HTUSER}..."
    htpasswd -bc "$HTPASSWD_FILE" "${HTUSER}" "${PASS}"
    chmod 644 "${HTPASSWD_FILE}"
fi