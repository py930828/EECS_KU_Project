LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
USE work.my_package.ALL;
USE work.math_real.ALL;

ENTITY RegFile IS
   PORT( 
      RA1      : IN  std_logic_vector (n_bits_of(reg_file_depth) - 1 DOWNTO 0);
      RA2 	   : IN  std_logic_vector (n_bits_of(reg_file_depth) - 1 DOWNTO 0);
      RegWrite : IN  std_logic;
      WA  	   : IN  std_logic_vector (n_bits_of(reg_file_depth) - 1 DOWNTO 0);
      WD  	   : IN  std_logic_vector (reg_file_width - 1 DOWNTO 0);
      clk      : IN  std_logic;
      rst      : IN  std_logic;
      RD1 	   : OUT std_logic_vector (reg_file_width - 1 DOWNTO 0);
      RD2 	   : OUT std_logic_vector (reg_file_width - 1 DOWNTO 0)
   );
END RegFile;

ARCHITECTURE behav OF RegFile IS

   -- Internal signal declarations
   SIGNAL reg_file  : mem_type(0 to reg_file_depth - 1);
   SIGNAL RA1_index : NATURAL  RANGE 0 TO reg_file_depth - 1;
   SIGNAL RA2_index : NATURAL  RANGE 0 TO reg_file_depth - 1;
   SIGNAL WA_index  : NATURAL  RANGE 0 TO reg_file_depth - 1;

BEGIN
   --- insert your code here ---
   
    process(rst, clk, RA1, RA2)
    begin
        WA_index <= to_integer(unsigned(WA));
        RA1_index <= to_integer(unsigned(RA1));
        RA2_index <= to_integer(unsigned(RA2));
        if (rst = '1') then
            for i in 0 to reg_file_depth - 1 loop
                reg_file(i) <= std_logic_vector(to_unsigned(0, WD'length));
            end loop;
        elsif (rising_edge(clk)) then
            if( RegWrite = '1' AND WA_index < reg_file_depth AND WA_index /= 0) then
                reg_file(WA_index) <= WD;
            end if;
        end if;
    end process;
    
    process(RA1_index, RA2_index, reg_file)
    begin
        
        if( RA1_index < reg_file_depth ) then  -- check for if RA1 is bigger than array size
            RD1 <= reg_file(RA1_index);
        else 
            RD1 <= (others => '0');
        end if;                                -- finish checking
        
        if( RA2_index < reg_file_depth ) then  -- check for if RA2 is bigger than array size
            RD2 <= reg_file(RA2_index);
        else 
            RD2 <= (others => '0');
        end if;                                 -- finish checking
    end process;


   -----------------------------

END behav;
