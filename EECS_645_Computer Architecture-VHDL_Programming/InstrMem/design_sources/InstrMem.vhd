LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;
USE work.my_package.ALL;
USE work.math_real.ALL;
USE ieee.numeric_std.ALL;

ENTITY InstrMem IS
   PORT( 
      A     : IN  std_logic_vector (n_bits_address - 1 DOWNTO 0);
      rst   : IN  std_logic;
      Instr : OUT std_logic_vector (instr_mem_width - 1 DOWNTO 0)
   );
END InstrMem;

ARCHITECTURE behav OF InstrMem IS

   -- Internal signal declarations
   SIGNAL instr_mem  : mem_type(0 to instr_mem_depth - 1);
   SIGNAL A_index : NATURAL  RANGE 0 TO instr_mem_depth - 1;

BEGIN
    
   --- insert your code here ---
   process(A)
    begin
        A_index <= to_integer(unsigned(A));
    end process;
    
    process(A_index, rst)
        begin
            if( rst = '1' ) then
                instr_mem <= my_program;
                Instr <= (others => '0');
            else
                Instr <= instr_mem(A_index);
            end if;
    end  process;
END behav;
