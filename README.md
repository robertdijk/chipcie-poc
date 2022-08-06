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
 - [ ] Add other pages that are wanted(general information, training sources, etc)\
    * [X] Add Contest page
    * [ ] Add example problem page
    * [ ] Add Training Sources page
 - [ ] Expand the archive
