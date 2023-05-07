<h1 align="center">
	libft
</h1>

<p align="center">
    <img alt="size" src="https://img.shields.io/tokei/lines/github/darrenkuro/42_libft">
</p>
<p align="center">
    <img alt="score" src="https://badge42.vercel.app/api/v2/clhcmu90l002108mts40mykbj/project/3081844">
</p>
This repo contains files for the libft project for 42 cursus. 

`Submitted` directory contains the version of the files turned in and passed all the tests as for May 2nd, 2023. There are, however, some known issues for edge cases (malloc failing in the middle of `ft_split`) and optimization failures (i.e. allocating more memory than it needs to.)

[![dlu's 42 Libft Score](https://badge42.vercel.app/api/v2/clhcmu90l002108mts40mykbj/project/3081844)](https://github.com/JaeSeoKim/badge42)

`Updated` directory contains the identical files that are optimized after submission, therefore although theoritically better versions, it hasn't been thoroughly tested. It is intended to use for future projects and includes the bonus part natively.

# TODO
- [ ] Fix `ft_split` to return NULL when malloc fails in the middle of the string (one of the substr returns null.)
- [ ] Optimize `ft_substr` to malloc the exact size for when length given is larger than the source string.
