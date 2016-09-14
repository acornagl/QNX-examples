# Stress the QNX's pseudo-files
I have the suspicious that both the QNX6.5 and the QNX6.6 version are not fast
enough to manage several consecutive open/close calls to the pseudo-files (with
read/write permission) that describe the processes information.
