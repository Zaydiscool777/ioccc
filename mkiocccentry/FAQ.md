# Frequently Asked Questions about the `mkiocccentry` repo

This is FAQ version **28.0.2 2024-10-09**.

<div id="toc"></div>

## Table of Contents

0. [Where can I download the mkiocccentry toolkit?](#download)

1. [How do I compile the mkiocccentry tools?](#compiling)

2. [How may I install the tools if I wish to, and is it required?](#install)

3. [What can I do if my system's tar(1) does not support the correct options?](#tar)

4. [How can I learn more about how to use the tools?](#help)

5. [How do I report bugs or other issues?](#bugs)

6. [How can I help test this repo?](#how-to-help)

7. [Why do these tools sometimes use the incorrect IOCCC terms?](#terms)

8. [How do I participate in the IOCCC?](#ioccc)

9. [How do I uninstall the toolkit?](#uninstalling)


<div id="download"></div>

## 0. Where can I find the mkiocccentry toolkit?

The `mkiocccentry` tool source code is found in the
[mkiocccentry repo](https://github.com/ioccc-src/mkiocccentry).
If you have not already done so, you may download the source by using `git
clone`:


```sh
git clone https://github.com/ioccc-src/mkiocccentry.git
```

If you don't have `git` you can instead
[download the zip file](https://github.com/ioccc-src/mkiocccentry/archive/refs/heads/master.zip)
and then extract that file.



<div id="compiling"></div>

## 1. How do I compile the mkiocccentry tools?

After downloading the repo (making sure that if you downloaded the zip file that
you unzip it first) move into the `mkiocccentry` directory:

```sh
cd mkiocccentry
```

and compile everything from scratch:

```sh
make clobber all
```

If all is well, you will find the `mkiocccentry` executable in your
local directory.  If something went wrong, see
<a href="#reporting-bugs">how do I report bugs or other issues?</a>

**NOTE**: the toolkit uses an import of the [dbg
repo](https://github.com/lcn2/dbg), the [dyn_array
repo](https://github.com/lcn2/dyn_array) and the [jparse
repo](https://github.com/xexyl/jparse). Although you may download, compile and
install those, this is **NOT** a requirement and they may in fact at some points
be different from the respective copies. The Makefiles here will link in the
libraries that are compiled here, and not any external libraries. Thus although
these libraries are needed for the tools, you do not need to install them in
your system.


<div id="install"></div>
<div id="installing"></div>


## 2.  How may I install the tools if I wish to, and is it required?

You do not need to install the code (see below) but it can be helpful to do so,
so you can run the tools from any directory including your submission directory;
that way, you do not have to specify paths.

If you do wish to install the toolkit, you can do:

```sh
make install
```

as either root or via sudo. By default this will install with the `PREFIX` of
`/usr/local` so the programs will be installed to `/usr/local/bin`, libraries in
`/usr/local/lib`, man pages in `/usr/local/share/man/man[138]` etc. If you wish
to have them elsewhere, for instance `/usr` or some other location, you can
override the default location with the `PREFIX` variable. For instance, to
install with the `PREFIX` of `/usr`:


```sh
make PREFIX=/usr install
```


### Is installing required?

No, installing the code in this repo is not necessary to use it. These tools
were designed to be used from the top level directory of the source, or after
installing, whichever you prefer.

You can simply execute the code from the top level directly of the source, after
compiling of course.

As `.` might not be (and almost certainly should NOT be) in your `$PATH`, you
might need to put `./` before the name of a command.

For example:

```sh
./mkiocccentry -h
```

However, it is much easier if you do run `make install` (as root or via sudo) as
then you can just run it from your submission's directory (the one you work on
it from) or anywhere else. On the other hand the `bug_report.sh` script needs to
be run from the repo directory itself. Of course, you should make sure you have
the latest version of the toolkit prior to using it!

<div id="tar"></div>

## 3. What can I do if my system's tar(1) does not support the correct options?

If your `tar` does not support the `-J` option you can either use a system
which does have such a `tar` or you can try downloading GNU Tar from
the [GNU website](https://www.gnu.org/software/tar/) and after extracting it,
compile it and then install it so that the tools may find it.

Some systems have a `GNU tar` that you can use. For instance FreeBSD has a
`gtar` command so if necessary you can use that. Note that you'll have to
specify in the tools (that require a correct `tar`) the `-t tar` option to make
this work.


<div id="help"></div>

## 4. How can I learn more about how to use the tools?

Assuming you have <a href="#download">downloaded</a> and <a
href="#compiling">compiled</a> the code you can get a quick reminder of command
options and arguments by use of the `-h` option of any tool:

For instance:

```sh
./mkiocccentry -h
./iocccsize -h
./chkentry -h
./txzchk -h
./test_ioccc/fnamchk -h
```

There are man pages that go into much more detail than the `-h` help modes. You
may use the `man(1)` command to read the man pages without having to install
them.

After compiling this code, various man pages are copied under the local `man/`
directory at the top of the source directory.

For example:

```sh
man man/man1/mkiocccentry.1
man man/man1/iocccsize.1
man man/man1/chkentry.1
man man/man1/txzchk.1
man man/man1/fnamchk.1
```

There are many other man pages under the `man/` directory for the curious to
read, using a similar technique.

If all that fails to satisfy your curiosity, we recommend you _"use the source,
Luke!"_ as you may find the code in this repo reasonably unobfuscated and fairly
well commented.

**NOTE**: there are other tools not listed above that are not an important part
of participating in the contest; look at the man pages, the Makefiles or
compiled tools for more details.


<div id="bugs"></div>
<div id="reporting-bugs"></div>

## 5. How do I report bugs or other issues?

If you've run into a problem with the repo and you think it is a bug then you
should [report it as a
bug](https://github.com/ioccc-src/mkiocccentry/issues/new?assignees=&labels=bug&projects=&template=bug_report.yml&title=%5BBug%5D+%3Ctitle%3E),
making sure to give as much information as possible.

To help us help you **PLEASE** run the following command from the **top level
mkiocccentry directory** (in other words, if you have [installed](#install) the
toolkit you **MUST** still run this from the toolkit directory):


```sh
make bug_report
```

and then attach the bug report log (see below about the filename).

You may also run the `bug_report.sh` tool directly:

```sh
./bug_report.sh -v 1
```

The bug report filename is in the format:
`bug-report.$(date +%Y%m%d.%H%M%S).txt` where:


- `%Y` is the four digit year (e.g. 2024).

- `%m` is the two digit month (01..12).

- `%d` is the two digit day of the month (e.g. 31).

- `%H` is the two digit hour of the day (00..23).

- `%M` is the two digit minute of the hour of the day (00..59); and

- `%S` is the two digit second of the minute (in the range 0..60).


The script that the make rule runs, `bug_report.sh`, will tell you the name of
the file to upload.

**NOTE**: the script might report that there is no problem but that does not
mean there is no bug; on the other hand even if it reports a problem it does not
necessarily mean there is a bug but you can report it as a bug as we can
hopefully help. Feel free to use your judgement in this matter but most likely
unless it's a feature request the best one is a bug report.

On the other hand, see the [SECURITY](SECURITY.md) file if you have a security
concern.

**NOTE**: the `bug_report.sh` script runs `test_ioccc/hostchk.sh` but you can
run it directly if you wish:


```sh
./test_ioccc/hostchk.sh
```


<div id="how-to-help"></div>

Thank you for any and all help!

Please see the
[README file in the test_ioccc subdirectory](https://github.com/ioccc-src/mkiocccentry/blob/master/test_ioccc/README.md)
for more details on what you can do to help us.


<div id="terms"></div>

## 7. Why do these tools sometimes use incorrect IOCCC terms?

According to the [Official IOCCC FAQ 6.9](https://www.ioccc.org/faq.html#terms)
this repo sometimes uses the wrong term.  For example the name `mkiocccentry(1)` contains
the name `entry` when the tool is dealing with a `submission`.  So
why don't we call the tool `mkiocccsubmission` and rename the this repo?

Because the name `mkiocccentry(1)` and this repo name was selected
before decisions were made in regards to the IOCCC term `entry`.
And besides, the name `mkiocccentry(1)` contains a fun pun.  And
renaming the repo and updating all the code and data files (of which there are
many) is not worth the hassle.

If the inconsistency bothers you, think of the name `mkiocccentry(1)`
as a hopeful sign that the `submission` it is processing might
actually win the IOCCC and become a winning entry.  :-)  After all,
some submissions do go on to become winners, so maybe yours will too. :-)

You may find inconsistent use of `Author(s)`,  `Entry`, and `Submission`
in this repo as well.  The above "excuse" for `entry` instead of `submission` is
just an example.

We made an attempt to correct some of the inconsistent use of the
terms `Author(s)`, `Entry`, and `Submission` in this repo.  If you DO
find a situation where the inconsistency is causing a problem and/or
confusion, please let us know in the way of a bug report or if you're sure that
it's correct, a pull request that corrects the mistake or mistakes. Please note
that if you do this you **MUST** run `make prep` or at least `make test`. Not
doing this poses a great risk of causing problems.

Note, however, that there are many cases where the words `entry` and/or
`entries` are actually correct: they would only be incorrect if they refer to an
IOCCC submission that has not won.  In other words if it refers to submission(s)
won then it should be `entry` (or `entries`).

<div id="ioccc"></div>

## 8. How do I participate in the IOCCC?

<!--XXX Update these links after the Great Fork Merge! -->
Please see the [official IOCCC website
FAQ](https://www.ioccc.org/faq.html) and in particular the
FAQ on
"[submitting](https://www.ioccc.org/faq.html#submit)",
the
FAQ on
"[Makefiles](https://www.ioccc.org/faq.html#makefile)",
the
FAQ on "[source code
filename](https://www.ioccc.org/faq.html#prog),
the
FAQ on
"[mkiocccentry](https://www.ioccc.org/faq.html#mkiocccentry),
the [Rules](https://www.ioccc.org/next/rules.html) and the
[Guidelines](https://www.ioccc.org/next/guidelines.html).

Pay especial care to [Rule
17](https://www.ioccc.org/next/rules.html#rule17)!


<div id="uninstalling"></div>
## 9. How do I uninstall the toolkit?

If you have installed the tools and you wish to uninstall them, you can do so
from the top level repo directory by typing:

```sh
make uninstall
```

as either root or via sudo.

Remember that if you installed with a different `PREFIX` you will have to use
that same `PREFIX` to successfully uninstall the programs, library and man
pages. For instance if you installed with the `PREFIX` of `/usr` you would type
instead:

```sh
make PREFIX=/usr uninstall
```

After this all the files installed should be removed. If this is not the case by
some chance it is likely a bug and you may report it as a bug
[here](https://github.com/ioccc-src/mkiocccentry/issues/new?assignees=&labels=bug&projects=&template=bug_report.yml&title=%5BBug%5D+%3Ctitle%3E).
