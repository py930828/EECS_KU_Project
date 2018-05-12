LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY arbiter_9consumers_ascending_priority_tb IS
END arbiter_9consumers_ascending_priority_tb;
 
ARCHITECTURE behavior OF arbiter_9consumers_ascending_priority_tb IS 
 
   -- Component Declaration for the Unit Under Test (UUT) 

	COMPONENT arbiter_9consumers_ascending_priority
	   GENERIC (n_consumers : NATURAL := 9);
	   PORT(clk     : IN    STD_LOGIC;
		rst     : IN    STD_LOGIC;
		REQ_VEC : IN    STD_LOGIC_VECTOR(n_consumers DOWNTO 1);
		ACK_VEC : OUT	STD_LOGIC_VECTOR(n_consumers DOWNTO 1)
	   );
	END COMPONENT;
   
   -- Generics
   CONSTANT n_consumers : NATURAL := 9;
   
   -- Inputs
   signal clk    : std_logic := '0';
   signal rst    : std_logic := '0';
   signal REQ_VEC : STD_LOGIC_VECTOR(n_consumers DOWNTO 1) := (others => '0');

   -- Outputs
   signal ACK_VEC : STD_LOGIC_VECTOR(n_consumers DOWNTO 1) := (others => '0');

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
   -- Instantiate the Unit Under Test (UUT)
   uut: arbiter_9consumers_ascending_priority 
   	GENERIC MAP (n_consumers => n_consumers)
   	PORT    MAP (clk         => clk,
   		     rst         => rst,
   		     REQ_VEC     => REQ_VEC,
   		     ACK_VEC     => ACK_VEC
        	    );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 3 clock periods.
		rst <= '1';
      wait for clk_period*3;	
		
		rst <= '0';
      wait for clk_period*3;

      -- insert stimulus here 

      REQ_VEC <= "111111111"; -- access to consumer 9
      wait for clk_period*3;

      REQ_VEC <= "100010011"; -- access to consumer 9
      wait for clk_period*3;
       
      REQ_VEC <= "000010011"; -- access to consumer 5
      wait for clk_period*3;
      
      REQ_VEC <= "001010011"; -- access to consumer 7
      wait for clk_period*3;
 
      REQ_VEC <= "000000011"; -- access to consumer 2
      wait for clk_period*3;
 
      REQ_VEC <= "010010011"; -- access to consumer 8
      wait for clk_period*3;

      REQ_VEC <= "010001011"; -- access to consumer 8
      wait for clk_period*3;

      REQ_VEC <= "000001011"; -- access to consumer 4
      wait for clk_period*3;

      REQ_VEC <= "000000011"; -- access to consumer 2
      wait for clk_period*3;

      REQ_VEC <= "000000001"; -- access to consumer 1
      wait for clk_period*3;
      
      REQ_VEC <= "000000000"; -- access to none
      wait for clk_period*3;

      REQ_VEC <= "000000001"; -- access to consumer 1
      wait for clk_period*3;

      REQ_VEC <= "000000011"; -- access to consumer 2
      wait for clk_period*3;

      REQ_VEC <= "000100011"; -- access to consumer 6
      wait for clk_period*3;

      REQ_VEC <= "000111111"; -- access to consumer 6
      wait for clk_period*3;

      REQ_VEC <= "100111111"; -- access to consumer 9
      wait for clk_period*3;

      REQ_VEC <= "010111111"; -- access to consumer 8
      wait for clk_period*3;

      REQ_VEC <= "110111111"; -- access to consumer 9
      wait for clk_period*3;

      REQ_VEC <= "111111111"; -- access to consumer 9
      wait for clk_period*3;

      REQ_VEC <= "100000001"; -- access to consumer 9
      wait for clk_period*3;

      REQ_VEC <= "000000001"; -- access to consumer 1
      wait for clk_period*3;

      REQ_VEC <= "000000101"; -- access to consumer 3
      wait for clk_period*3;

      REQ_VEC <= "000000111"; -- access to consumer 3
      wait for clk_period*3;

      REQ_VEC <= "000001100"; -- access to consumer 4
      wait for clk_period*3;

      REQ_VEC <= "100001100"; -- access to consumer 9
      wait for clk_period*3;

		rst <= '1';
      wait for clk_period*3;	
		
		rst <= '0';
      wait for clk_period*3;      
		
      wait;
   end process;

END;
