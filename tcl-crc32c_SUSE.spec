%{!?directory:%define directory /usr}

%define buildroot %{_tmppath}/%{name}-%{version}

Name:          tcl-crc32c
Summary:       Tcl bindings for crc32c library
Version:       0.3
Release:       0
License:       MIT
Group:         Development/Libraries/Tcl
Source:        %name-%version.tar.gz
URL:           https://github.com/ray2501/tcl-crc32c
BuildRequires: autoconf
BuildRequires: make
BuildRequires: gcc
BuildRequires: libcrc32c-devel
BuildRequires: tcl-devel >= 8.5
Requires:      tcl >= 8.5
BuildRoot:     %{buildroot}

%description
This extension is Tcl bindings for Google crc32c library.

%prep
%setup -q -n %{name}-%{version}

%build
./configure \
	--prefix=%{directory} \
	--exec-prefix=%{directory} \
	--libdir=%{directory}/%{_lib}
make 

%install
make DESTDIR=%{buildroot} pkglibdir=%{tcl_archdir}/%{name}%{version} install

%clean
rm -rf %buildroot

%files
%defattr(-,root,root)
%{tcl_archdir}
