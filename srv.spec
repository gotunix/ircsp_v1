%define ver      5.1
%define rel      1
%define prefix   /usr

Summary: IRC Services Package
Name: ircsp
Version: %ver
Release: %rel
Copyright: Genereal Public License
Group: Lostworld Development
Packager: Justin Ovens (ice95@lostworld.net)
URL: http://www.lostworld.net

%build
if [ ! -z "`echo -n ${RPM_OPT_FLAGS} | grep pentium`" ]; then
  if [ ! -z "`which egcs`" ]; then
    CC="egcs" 
  else
    if [ ! -z "`which pgcc`" ]; then
      CC="pgcc"
    fi
  fi
  CFLAGS="${RPM_OPT_FLAGS}"
else
  CFLAGS="${RPM_OPT_FLAGS}"
fi
if [ ! -f configure ]; then
  CFLAGS="$RPM_OPT_FLAGS" ./autogen.sh --prefix=%prefix --enable-fsstd
else
  CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%prefix --enable-fsstd
fi
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{prefix} install

cd $RPM_BUILD_ROOT%{prefix}/
chown -R 0.0 *

%files
%defattr(-, root, root)

