Name:       bundle
Summary:    String key-val dictionary ADT
Version:    0.1.36
Release:    1
Group:      System/Libraries
License:    Apache-2.0
Source0:    bundle-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  cmake
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-base-common)

%description
Simple string key-val dictionary ADT

%package devel
Summary:    String key-val dictionary ADT (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Simple string key-val dictionary ADT (devel)

%prep
%setup -q -n %{name}-%{version}

%build
export CFLAGS="$CFLAGS -Wall -Werror -Wno-unused-function"
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest bundle.manifest
%defattr(-,root,root,-)
%{_libdir}/libbundle.so.*
/usr/share/license/%{name}

%files devel
%defattr(-,root,root,-)
%{_includedir}/bundle.h
%{_includedir}/bundle_internal.h
%{_libdir}/pkgconfig/bundle.pc
%{_libdir}/libbundle.so
