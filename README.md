# SToESD_II_2019-20

Ausgewählte Themen der Embedded Software Entwicklung II
Selected Topics of Embedded Software Development II
# Code Changes
  - first change ioread & iowrite
    - ```
      //new code_app

	  __u32 val = 0;
	  val=TRNG_512_test.rand[0];

	  ret_val = ioctl(dd, IOCTL_READ_RAM_B, &val);
	  printf("%08x",val);

	  //new_code_driver

	  u32 val = 0;
	  case IOCTL_READ_RAM_B:
      get_user(val, (u32 *)arg);
      iowrite32(val, (MWMAC_RAM_ptr+0x3+0x4));
	  val = ioread32((MWMAC_RAM_ptr+0x3+0x4));
	  put_user(val, (u32 *)arg);
	  break;
		
      //header

      #define 	IOCTL_READ_RAM_B		_IOR(IOCTL_BASE, 6, __u32) 
      ```
