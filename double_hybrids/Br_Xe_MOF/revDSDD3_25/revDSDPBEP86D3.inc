    &XC
    # This keyword is necessary if you use ADMM with the default exchange correlation correction because the analytical terms are not available for the employed functionals.
      2ND_DERIV_ANALYTICAL .FALSE.
      STEP_SIZE 1.0E-3
      &XC_FUNCTIONAL
      # You can also use the CP2K versions if necessary, here it is the LibXC versions.
       &GGA_X_PBE
         SCALE 0.31
       &END
       &GGA_C_P86
         SCALE 0.4296
       &END
       # The longrange correction, if necessary
       &PBE_HOLE_T_C_LR
         CUTOFF_RADIUS ${MY_CUTOFF_RADIUS}
         SCALE_X 0.69
       &END PBE_HOLE_T_C_LR
      &END XC_FUNCTIONAL
      &HF
        # Depends on your functional
        FRACTION 0.69
        &SCREENING
          # Chose these parameters
	  ###   EPS_SCHWARZ 5.0E-8
	  EPS_SCHWARZ 1.0E-9
          EPS_SCHWARZ_FORCES 1.0E-6
          SCREEN_ON_INITIAL_P FALSE
        &END SCREENING
        &INTERACTION_POTENTIAL
          # Depends on your functional
          POTENTIAL_TYPE TRUNCATED
          CUTOFF_RADIUS ${MY_CUTOFF_RADIUS}
          # Adjust this file name accordingly
          T_C_G_DATA t_c_g.dat
        &END INTERACTION_POTENTIAL
        &MEMORY
          # Chose it accordingly
          MAX_MEMORY 3000
        &END MEMORY
      &END HF
      &WF_CORRELATION
        &RI_MP2
	  #  &CPHF
	  #    EPS_CONV ${EPS_CONV-1.0E-4}
	  #    MAX_ITER ${MAX_ITER-30}
	  #  &END
          # Do not touch this parameter if gradient is needed. 
	  # Also keep 1 for open shell systems. 
	  # Improves communication by distributing workload. 
	  # sqrt of occupited orbitals as maximum value.
	  BLOCK_SIZE 1
          # In my calculations, I have to set this keyword, try it without if possible.
	  #	  FREE_HFX_BUFFER .FALSE.
        &END
        &INTEGRALS
          &WFC_GPW
          # These parameters have to be chosen by you 
            CUTOFF  150
            REL_CUTOFF 50
          &END
        &END
        # This parameter should be chosen as small as possible and must be a divisor of the number of MPI ranks
        # In certain cases, you might run out of memory, increase it accordingly then. 
	# Useful if you run out of memory but can compromise performances.
        GROUP_SIZE 1
        # Set it as high as possible such that the MP2 code has enough memory
        MEMORY 3000
        # Set the parameters according to your functional
        SCALE_T  0.0799
        SCALE_S  0.5785
      &END
      &vdW_POTENTIAL
         DISPERSION_FUNCTIONAL PAIR_POTENTIAL
         &PAIR_POTENTIAL
           TYPE DFTD3(BJ)
           PARAMETER_FILE_NAME dftd3.dat
           D3BJ_SCALING 0.4377 0.0 0.0 5.5
         &END PAIR_POTENTIAL
      &END vdW_POTENTIAL
    &END XC
#    &AUXILIARY_DENSITY_MATRIX_METHOD
#      METHOD BASIS_PROJECTION
#      ADMM_PURIFICATION_METHOD NONE
#      # You can try out different correction functionals (see manual)
#      EXCH_CORRECTION_FUNC DEFAULT
#    &END
