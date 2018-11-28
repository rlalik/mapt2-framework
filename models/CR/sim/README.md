Cosmic Radiation model
======================

1. Preparations
---------------

Make sure following direcotries exists inside

    log/
    cards_jobs/
    output/

`output` can be a symlink to other locaton for mass storage of files.

Please also copy in `geometry.txt` for simulations and `params.txt` for dst runs.

2. Preparing models
-------------------

Go to `cards_gps_CR`. All model components are in the txt files, with name encoding `A_Z_element.txt` except for a proton which is `1_H.txt`. Protons (hydrogen) are used as a reference (intensity 1).

Run script `./gen_card.py` (requires python3, not tested with python2). It will parse all txt files, calculate integrals and use it to calculate intensities relative to Hydrogen (1). Output will go to `stdout`, you can use e.g. `./gen_card.py | tee gpc_cr.mac` to write to file.

3. Running sumulations
----------------------

Use template script from `CR_model.sh.example` and copy it as your script, e.g.

    cp CR_model.sh.example CR_model.sh

Edit the script (line #34) to put your profile there. Comment or remove line #32. Uncomment line #82 is you want dst to run automatically after simulation. Set yourworking directory in line #2.

You can also change number of jobs (line #4) and number of events (line #13).

Make sure directories from point 1. exists, otherwise simulation will not run.

Start simulation with `qsub CR_model.sh`. If you need run only dst: `qsub CR_dst.txt`.

If you want to remove output file which already exists, uncomment line #72 (file will be overriden anyway).

Simulation will skip jobs for which files which are generated. if you want to force run, comment line #74.

If you want to remove simulation file after the dst is done, uncommend line #61 in the `CR_dst.sh` file.
