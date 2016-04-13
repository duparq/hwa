=======
 Tools
=======

.. module:: serial

serial.tools.list_ports
=======================
.. module:: serial.tools.list_ports

This module can be executed to get a list of ports (``python -m
serial.tools.list_ports``). It also contains the following functions.


.. function:: comports()

    :return: an iterable that yields :class:`ListPortInfo` objects.

    The function returns an iterable that yields tuples of three strings:

    - port name as it can be passed to :class:`serial.Serial` or
      :func:`serial.serial_for_url`
    - description in human readable form
    - sort of hardware ID. E.g. may contain VID:PID of USB-serial adapters.

    Items are returned in no particular order. It may make sense to sort the
    items. Also note that the reported strings are different across platforms
    and operating systems, even for the same device.

    .. note:: Support is limited to a number of operating systems. On some
              systems description and hardware ID will not be available
              (``None``).

    :platform: Posix (/dev files)
    :platform: Linux (/dev files, sysfs and lsusb)
    :platform: OSX (iokit)
    :platform: Windows (setupapi, registry)


.. function:: grep(regexp)

    :param regexp: regular expression (see stdlib :mod:`re`)
    :return: an iterable that yields :class:`ListPortInfo` objects, see also :func:`comports`.

    Search for ports using a regular expression. Port name, description and
    hardware ID are searched (case insensitive). The function returns an
    iterable that contains the same tuples that :func:`comport` generates, but
    includes only those entries that match the regexp.

.. class:: ListPortInfo

    This object holds information about a serial port. It supports indexed
    access for backwards compatibility, as in ``port, desc, hwid = info``.

    .. attribute:: device

        Full device name/path, e.g. ``/dev/ttyUSB0``. This is also the
        information returned as first element when accessed by index.

    .. attribute:: name

        Short device name, e.g. ``ttyUSB0``.

    .. attribute:: description

        Human readable description or ``n/a``. This is also the information
        returned as second element when accessed by index.

    .. attribute:: hwid

        Technical description or ``n/a``. This is also the information
        returned as third element when accessed by index.

    USB specific data, these are all ``None`` if it is not a USB device (or the
    platform does not support extended info).

    .. attribute:: vid

        USB Vendor ID (integer, 0...65535).

    .. attribute:: pid

        USB product ID (integer, 0...65535).

    .. attribute:: serial_number

        USB serial number as a string.

    .. attribute:: location

        USB device location string ("<bus>-<port>[-<port>]...")

    .. attribute:: manufacturer

        USB manufacturer string, as reported by device.

    .. attribute:: product

        USB product string, as reported by device.

    .. attribute:: interface

        Interface specifc description, e.g. used in compound USB devices.

    Comparison operators are implemented such that the ``ListPortInfo`` objects
    can be sorted by ``device``. Strings are split into groups of numbers and
    text so that the order is "natural" (i.e. ``com1`` < ``com2`` <
    ``com10``).


**Command line usage**

Help for ``python -m serial.tools.list_ports``::

    usage: list_ports.py [-h] [-v] [-q] [-n N] [regexp]

    Serial port enumeration

    positional arguments:
      regexp         only show ports that match this regex

    optional arguments:
      -h, --help     show this help message and exit
      -v, --verbose  show more messages
      -q, --quiet    suppress all messages
      -n N           only output the N-th entry

Examples:

- List all ports with details::

    $ python -m serial.tools.list_ports -v
    /dev/ttyS0
        desc: ttyS0
        hwid: PNP0501
    /dev/ttyUSB0
        desc: CP2102 USB to UART Bridge Controller
        hwid: USB VID:PID=10C4:EA60 SER=0001 LOCATION=2-1.6
    2 ports found


- List the 2nd port matching a USB VID:PID pattern::

    $ python -m serial.tools.list_ports 1234:5678 -q -n 2
    /dev/ttyUSB1

.. versionadded:: 2.6
.. versionchanged:: 3.0 returning ``ListPortInfo`` objects instead of a tuple


.. _miniterm:

serial.tools.miniterm
=====================
.. module:: serial.tools.miniterm

This is a console application that provides a small terminal application.
Miniterm itself does not implement any terminal features such as VT102
compatibility. However it may inherit these features from the terminal it is run.
For example on GNU/Linux running from an xterm it will support the escape
sequences of the xterm. On Windows the typical console window is dumb and does
not support any escapes. When ANSI.sys is loaded it supports some escapes.

Miniterm::

    --- Miniterm on /dev/ttyS0: 9600,8,N,1 ---
    --- Quit: Ctrl+]  |  Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---

Command line options can be given so that binary data including escapes for
terminals are escaped or output as hex.

Miniterm supports :rfc:`2217` remote serial ports and raw sockets using :ref:`URLs`
such as ``rfc2217:://<host>:<port>`` respectively ``socket://<host>:<port>`` as
*port* argument when invoking.

Command line options ``python -m serial.tools.miniterm -h``::

    usage: miniterm.py [-h] [--parity {N,E,O,S,M}] [--rtscts] [--xonxoff]
                       [--rts RTS] [--dtr DTR] [-e] [--encoding CODEC] [-f NAME]
                       [--eol {CR,LF,CRLF}] [--raw] [--exit-char NUM]
                       [--menu-char NUM] [-q] [--develop]
                       [port] [baudrate]

    Miniterm - A simple terminal program for the serial port.

    positional arguments:
      port                  serial port name
      baudrate              set baud rate, default: 9600

    optional arguments:
      -h, --help            show this help message and exit

    port settings:
      --parity {N,E,O,S,M}  set parity, one of {N E O S M}, default: N
      --rtscts              enable RTS/CTS flow control (default off)
      --xonxoff             enable software flow control (default off)
      --rts RTS             set initial RTS line state (possible values: 0, 1)
      --dtr DTR             set initial DTR line state (possible values: 0, 1)
      --ask                 ask again for port when open fails

    data handling:
      -e, --echo            enable local echo (default off)
      --encoding CODEC      set the encoding for the serial port (e.g. hexlify,
                            Latin1, UTF-8), default: UTF-8
      -f NAME, --filter NAME
                            add text transformation
      --eol {CR,LF,CRLF}    end of line mode
      --raw                 Do no apply any encodings/transformations

    hotkeys:
      --exit-char NUM       Unicode of special character that is used to exit the
                            application, default: 29
      --menu-char NUM       Unicode code of special character that is used to
                            control miniterm (menu), default: 20

    diagnostics:
      -q, --quiet           suppress non-error messages
      --develop             show Python traceback on error


Miniterm supports some control functions. Typing :kbd:`Ctrl+T Ctrl+H` when it is
running shows the help text::

    --- pySerial (3.0a) - miniterm - help
    ---
    --- Ctrl+]   Exit program
    --- Ctrl+T   Menu escape key, followed by:
    --- Menu keys:
    ---    Ctrl+T  Send the menu character itself to remote
    ---    Ctrl+]  Send the exit character itself to remote
    ---    Ctrl+I  Show info
    ---    Ctrl+U  Upload file (prompt will be shown)
    ---    Ctrl+A  encoding
    ---    Ctrl+F  edit filters
    --- Toggles:
    ---    Ctrl+R  RTS   Ctrl+D  DTR   Ctrl+B  BREAK
    ---    Ctrl+E  echo  Ctrl+L  EOL
    ---
    --- Port settings (Ctrl+T followed by the following):
    ---    p          change port
    ---    7 8        set data bits
    ---    N E O S M  change parity (None, Even, Odd, Space, Mark)
    ---    1 2 3      set stop bits (1, 2, 1.5)
    ---    b          change baud rate
    ---    x X        disable/enable software flow control
    ---    r R        disable/enable hardware flow control

.. versionchanged:: 2.5
    Added :kbd:`Ctrl+T` menu and added support for opening URLs.
.. versionchanged:: 2.6
    File moved from the examples to :mod:`serial.tools.miniterm`.
.. versionchanged:: 3.0
    Apply encoding on serial port, convert to Unicode for console.
    Added new filters, default to stripping terminal control sequences.
    Added --ask option.

