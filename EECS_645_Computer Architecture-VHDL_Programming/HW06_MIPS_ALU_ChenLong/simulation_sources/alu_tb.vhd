LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE work.my_package.ALL;
USE work.math_real.ALL;
 
ENTITY alu_tb IS
END alu_tb;
 
ARCHITECTURE behavior OF alu_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
	COMPONENT ALU
	   PORT( 
	      A           : IN     std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
	      ALU_control : IN     std_logic_vector (n_bits_of(n_functions_alu) - 1 DOWNTO 0);
	      B           : IN     std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
	      C           : OUT    std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
	      zero        : OUT    std_logic;
	      overflow    : OUT    std_logic
	   );
	END COMPONENT;	

   --Inputs
   signal A : std_logic_vector(n_bits_alu  - 1 downto 0) := (others => '0');
   signal ALU_control : std_logic_vector(n_bits_of(n_functions_alu) - 1 downto 0) := (others => '0');
   signal B : std_logic_vector(n_bits_alu  - 1 downto 0) := (others => '0');

   --Outputs
   signal C : std_logic_vector(n_bits_alu  - 1 downto 0);
   signal zero : std_logic;
   signal overflow : std_logic;
   
   constant delay_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: ALU PORT MAP (
          A => A,
          ALU_control => ALU_control,
          B => B,
          C => C,
          zero => zero,
          overflow => overflow
        );

   -- Stimulus process
   stim_proc: process
   begin		
      -- insert stimulus here
		A <= "00000000000000000000000000000011";
		B <= "00000000000000000000000000001000";
		
		ALU_control <= "0000";
		wait for delay_period*3; 
		
		ALU_control <= "0001";
		wait for delay_period*3; 
		
		ALU_control <= "0010";
		wait for delay_period*3;		

		ALU_control <= "0110";
		wait for delay_period*3; 
		
		ALU_control <= "0111";
		wait for delay_period*3;
		
		ALU_control <= "1100";
		wait for delay_period*3;		

		B <= "00000000000000000000000000000011";
		A <= "00000000000000000000000000001000";
		
		ALU_control <= "0000";
		wait for delay_period*3; 
		
		ALU_control <= "0001";
		wait for delay_period*3; 
		
		ALU_control <= "0010";
		wait for delay_period*3;	

		ALU_control <= "0110";
		wait for delay_period*3; 
		
		ALU_control <= "0111";
		wait for delay_period*3;
		
		ALU_control <= "1100";
		wait for delay_period*3;	


		A <= "01000000000000000000000000000011";
		B <= "01000000000000000000000000001000";
		
		ALU_control <= "0010";
		wait for delay_period*3;		

		ALU_control <= "0110";
		wait for delay_period*3; 

		B <= "01000000000000000000000000000011";
		A <= "01000000000000000000000000001000";
		
		ALU_control <= "0010";
		wait for delay_period*3;		

		ALU_control <= "0110";
		wait for delay_period*3; 

		A <= "10000000000000000000000000000011";
		B <= "10000000000000000000000000001000";
		
		ALU_control <= "0010";
		wait for delay_period*3;		

		ALU_control <= "0110";
		wait for delay_period*3; 

		B <= "10000000000000000000000000000011";
		A <= "10000000000000000000000000001000";
		
		ALU_control <= "0010";
		wait for delay_period*3;		

		ALU_control <= "0110";
		wait for delay_period*3; 

      wait;
   end process;

END;
