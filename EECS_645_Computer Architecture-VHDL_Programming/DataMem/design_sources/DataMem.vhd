LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;
USE work.my_package.ALL;
USE work.math_real.ALL;
USE ieee.numeric_std.ALL;

ENTITY DataMem IS
   PORT( 
      A        : IN  std_logic_vector (n_bits_address - 1 DOWNTO 0);
      MemWrite : IN  std_logic;
      WD       : IN  std_logic_vector (data_mem_width - 1 DOWNTO 0);
      clk      : IN  std_logic;
      rst      : IN  std_logic;
      RD       : OUT std_logic_vector (data_mem_width - 1 DOWNTO 0)
   );
END DataMem;

ARCHITECTURE behav OF DataMem IS

   -- Internal signal declarations
   SIGNAL data_mem  : mem_type(0 to data_mem_depth - 1);
   SIGNAL A_index : NATURAL  RANGE 0 TO data_mem_depth - 1;

BEGIN

   --- insert your code here ---
    process(rst, clk, A)
           begin
               A_index <= to_integer(unsigned(A));
               if (rst = '1') then
                   for i in 0 to data_mem_depth - 1 loop
                       data_mem(i) <= std_logic_vector(to_unsigned(0, WD'length));
                   end loop;
               elsif (rising_edge(clk)) then
                   if( MemWrite = '1' AND A_index < data_mem_depth ) then
                       data_mem(A_index) <= WD;
                   end if;
               end if;
           end process;
           
   process(A_index, data_mem)
           begin
               if( A_index < data_mem_depth ) then  -- check for if RA1 is bigger than array size
                   RD <= data_mem(A_index);
               else 
                   RD <= data_mem(0);
               end if;                                -- finish checking
 
           end process;


   -----------------------------

END behav;
