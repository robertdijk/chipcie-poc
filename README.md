# Proof of Concept new CHipCie site

## Before you Start

This repository use [lfs](https://git-lfs.github.com/) for large files. make sure you have lfs installed and configured
on your local system.

For downloading the theme for the first time use `git submodule update --init --recursive`.

## Idea
This poc is build in [hugo](https://gohugo.io). The concept for the poc is to make adding the problemset(and news and other updates)
easier. Tekst can be typed is MD script. Hugo generate an optimezed text only website, which can be hosted in a docker container.

For problemsets etc. in the data folder add the correct data in a yml(e.g. [2021.yaml](data/archive/dapc/2021.yaml)).
The pdfs/zip can be added in the [static/archive](static/archive) folder in the year and type of contest.

A table is generated based on the layout defined [here](layouts/partials/archive-table.html).
The table itself is generated [here](layouts/shortcodes). A shortcode per type of contest is required with this setup.

## Running
For development run `hugo serve` to run the application and then visit [http://localhost:1313](http://localhost:1313).


## Todo's and improvements
 - [X] How to deal with scoreboards?
 - [ ] Figure out if there is enough lfs space for all years
 - [X] Fix layout (especially of the table)
 - [ ] Add other pages that are wanted(general information, training sources, etc)
    * [X] Add Contest page
    * [ ] Add example problem page
    * [X] Add Training Sources page
 - [X] Expand the archive
   * [X] Add archive files for DAPC 
   * [X] Add archive files for BAPC 
   * [X] Add archive files for NWERC 
   * [X] Add archive files for FPC 
   * [X] Reverse the table to have the latest contest at the top
   * [X] Add photo links from previous contests

## Future Todo's
 - [ ] Scan in old problem sets (marked to be in the old physical problem set archive)
   - [ ] DAPC 1990, 1991, 1992
   - [ ] NKP 1992, 1994, 1995, 2001(maybe, hopefully)
   - [ ] NWERC 1988, 1990, 1991, 1995 (double check 1989 if only 4 problems)
 - [ ] Search old chipcie drive for scoreboard dkp 2011 and 1998-
 - [ ] Search old CHipCie drive for problemsets FPC 2017, 2013, 2010, 2009, 2008, 2005
 - [ ] Add pictures from new ch picture site once it works again(dapc 2019 and up) 
