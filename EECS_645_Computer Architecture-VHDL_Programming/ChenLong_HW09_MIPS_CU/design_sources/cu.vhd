LIBRARY ieee;
USE ieee.std_logic_unsigned.all;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
USE work.my_package.ALL;
USE work.math_real.ALL;

ENTITY CU IS
   PORT( 
      Instr      : IN     std_logic_vector (n_bits_instr - 1 DOWNTO 0);
      ALUControl : OUT    std_logic_vector (n_bits_of(n_functions_alu) - 1 DOWNTO 0);
      ALUSrc     : OUT    std_logic;
      BEQ        : OUT    std_logic;
      J          : OUT    std_logic;
      MemToReg   : OUT    std_logic;
      MemWrite   : OUT    std_logic;
      RegDst     : OUT    std_logic;
      RegWrite   : OUT    std_logic
   );
END CU;

ARCHITECTURE behav OF CU IS
	SIGNAL opcode : NATURAL RANGE 0 TO (2**(opcode_end - opcode_start + 1) - 1);
	SIGNAL funct  : NATURAL RANGE 0 TO (2**(funct_end - funct_start + 1) - 1);
	SIGNAL ALUControl_int : NATURAL RANGE 0 TO (n_functions_alu - 1);

BEGIN
process(Instr)
begin
    opcode <= to_integer(unsigned(Instr(n_bits_instr-1 DOWNTO n_bits_instr-6)));
    funct <= to_integer(unsigned(Instr(5 DOWNTO 0)));
    case opcode is --case for opcode, define everyt output
        when 0 =>
            case funct is --case for funct, define ALUControl
                when 36 => 
                    ALUControl <= (others => '0');
                when 37 =>
                    ALUControl <= (0 => '1', others => '0');
                when 32 =>
                    ALUControl <= (1 => '1', others => '0');
                when 34 =>
                    ALUControl <= (1 => '1', 2 => '1', others => '0');
                when 42 =>
                    ALUControl <= (0 => '1', 1 => '1', 2 => '1', others => '0');
                when 39 =>
                     ALUControl <= (2 => '1', 3 => '1',  others => '0');
                when others =>
                    ALUControl <= (others => '0');
              end case; --end case for funct
      when 35 =>
        ALUControl <= (1 => '1', others => '0');
      when 43 =>
        ALUControl <= (1 => '1', others => '0');
      when 4 =>
        ALUControl <= (1 => '1', 2 => '1', others => '0');
      when 2 =>
        ALUControl <= ( others => '0');
      when 8 =>
        ALUControl <= (1 => '1', others => '0');
      when others =>
        ALUControl <= (others => '0');
      end case; -- end case for opcode;
   end process;
   RegDst <= '1' when opcode = 0 else '0';
   ALUSrc <= '1' when opcode = 35 or opcode = 43 else '0';
   MemtoReg <= '1' when opcode = 35 else '0';
   RegWrite <= '1' when opcode = 0 or opcode = 35 or opcode = 8 else '0';
   MemWrite <= '1' when opcode = 43 else '0';
   BEQ <= '1' when opcode = 4 else '0';
   J <= '1' when opcode = 2 else '0';
   -----------------------------

END behav;
