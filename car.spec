Summary: Cure your bad habit of mistyping
Summary(ja): キータイプ矯正ソフト
Name: car
Version: 1.0.0
Release: git_%{_commit_id}%{?dist}
License: MIT
URL: https://github.com/KusaReMKN/car
Group: Amusements/Games
Vendor: KusaReMKN
Packager: IchikawaYukko
BuildArch: x86_64
BuildRequires: ncurses-devel >= 5.9
Source: %{name}-%{version}-%{release}.src.tar.gz
Prefix: /usr


%description
Cars run across your terminal when you type "car" as you meant to type "cat". It's just a joke command, and not useful at all.

This is forked from sl by mtoyoda.

Original Copyright: sl Copyright 1993,1998,2014 Toyoda Masashi 


%description -l ja
sl の cat 版です(?)。 たくさんの引数を指定すると車が渋滞します。

Original Copyright: sl Copyright 1993,1998,2014 Toyoda Masashi (mtoyoda@acm.org)


# 更新履歴
%changelog
* Mon Apr 28 2025 IchikawaYukko
- First RPM package release


%prep
###  Binaries ###
#echo "BUILDROOT = "%{buildroot}
mkdir -p %{buildroot}/usr/bin/
mkdir -p %{buildroot}/usr/share/man/man1
mkdir -p %{buildroot}/usr/share/man/ja/man1

#echo "SRC_ROOT = $SRC_ROOT"
cp $SRC_ROOT/car %{buildroot}/usr/bin
gzip -9 -c $SRC_ROOT/car.1 > %{buildroot}/usr/share/man/man1/car.1.gz
gzip -9 -c $SRC_ROOT/car.1.ja > %{buildroot}/usr/share/man/ja/man1/car.1.gz

### Sources ###
cp $SRC_ROOT/car.c %{_sourcedir}/car.c
cp $SRC_ROOT/car.h %{_sourcedir}/car.h
tar cfz %{_sourcedir}/%{name}-%{version}-%{release}.src.tar.gz -C %{_sourcedir} car.c car.h
exit


%files
%attr(0755, root, root) /usr/bin/*
%attr(0664, root, root) /usr/share/man/man1/*
%attr(0664, root, root) /usr/share/man/ja/man1/*


%clean
rm -rf %{buildroot}/usr
ls -lZ %{_srcrpmdir}/* %{_rpmdir}/x86_64/*

