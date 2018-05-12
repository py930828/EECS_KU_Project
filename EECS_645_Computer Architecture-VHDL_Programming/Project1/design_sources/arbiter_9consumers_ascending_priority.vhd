LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;
use ieee.numeric_std.all;

ENTITY arbiter_9consumers_ascending_priority IS
   GENERIC (n_consumers : NATURAL := 9);
   PORT(clk     : IN    STD_LOGIC;
        rst     : IN    STD_LOGIC;
        REQ_VEC : IN    STD_LOGIC_VECTOR(n_consumers DOWNTO 1);
        ACK_VEC : OUT	STD_LOGIC_VECTOR(n_consumers DOWNTO 1)
   );
END arbiter_9consumers_ascending_priority;

ARCHITECTURE behav_priority OF arbiter_9consumers_ascending_priority IS

   -- Architecture Declarations  
   SIGNAL current_state, next_state : INTEGER RANGE 0 TO n_consumers;
   SIGNAL input : STD_LOGIC_VECTOR(n_consumers DOWNTO 1);

BEGIN
   ----------------------------------------------------------------------------
   memory_elements : PROCESS(clk, rst)
   ----------------------------------------------------------------------------
   BEGIN
    if(rst = '1') then
        current_state <= 0;
    else
        current_state <= next_state;
    end if;

   END PROCESS memory_elements;
   ----------------------------------------------------------------------------
   
   ----------------------------------------------------------------------------
   state_logic : PROCESS (REQ_VEC, current_state)
   ----------------------------------------------------------------------------
   BEGIN
   next_state <= current_state;
   CASE current_state IS
        WHEN 0 => -- No access State
            if REQ_VEC = "000000000" then
                next_state <= 0;
            elsif REQ_VEC = "000000001" then
                next_state <= 1;
            elsif std_match(REQ_VEC, "00000001-") then
                next_state <= 2;
            elsif std_match(REQ_VEC, "0000001--") then
                next_state <= 3; 
            elsif std_match(REQ_VEC, "000001---") then
                next_state <= 4;
            elsif std_match(REQ_VEC, "00001----") then
                next_state <= 5;
            elsif std_match(REQ_VEC, "0001-----") then
                 next_state <= 6;
            elsif std_match(REQ_VEC, "001------") then
                 next_state <= 7;
            elsif std_match(REQ_VEC, "01-------") then
                 next_state <= 8;
            elsif std_match(REQ_VEC, "1--------") then
                 next_state <= 9;
            end if;
        WHEN 1 =>
            if REQ_VEC = "000000001" then
                next_state <= 1;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8) OR REQ_VEC(7) OR REQ_VEC(6) OR REQ_VEC(5) OR REQ_VEC(4) OR REQ_VEC(3) OR REQ_VEC(2)) = '1') then
                next_state <= 0;   
            else
                next_state <= 0;
            end if;
        WHEN 2 =>
            if std_match(REQ_VEC, "00000001-") then
                next_state <= 2;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8) OR REQ_VEC(7) OR REQ_VEC(6) OR REQ_VEC(5) OR REQ_VEC(4) OR REQ_VEC(3)) = '1') then
                next_state <= 0;   
            elsif REQ_VEC(2) = '0' then
                next_state <= 0;
            end if;
        WHEN 3 =>
            if std_match(REQ_VEC, "0000001--") then
                next_state <= 3;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8) OR REQ_VEC(7) OR REQ_VEC(6) OR REQ_VEC(5) OR REQ_VEC(4)) = '1') then
                next_state <= 0;   
            elsif REQ_VEC(3) = '0' then
                next_state <= 0;
            end if;
        WHEN 4 =>
            if std_match(REQ_VEC, "000001---") then
                next_state <= 4;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8) OR REQ_VEC(7) OR REQ_VEC(6) OR REQ_VEC(5))  = '1') then
                next_state <= 0;   
            elsif REQ_VEC(4) = '0' then
                next_state <= 0;
            end if;
        WHEN 5 =>
            if std_match(REQ_VEC, "00001----") then
                next_state <= 5;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8) OR REQ_VEC(7) OR REQ_VEC(6)) = '1') then
                next_state <= 0;   
            elsif REQ_VEC(5) = '0' then
                next_state <= 0;
            end if;
        WHEN 6 => 
            if std_match(REQ_VEC, "0001-----") then
                next_state <= 6;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8) OR REQ_VEC(7)) = '1') then
                next_state <= 0;   
            elsif REQ_VEC(6) = '0' then
                next_state <= 0;
            end if;
        WHEN 7 =>
            if std_match(REQ_VEC, "001------") then
                next_state <= 7;
            elsif ( (REQ_VEC(9) OR REQ_VEC(8)) = '1') then
                next_state <= 0;   
            elsif REQ_VEC(7) = '0'then
                next_state <= 0;
            end if;
        WHEN 8 =>
            if std_match(REQ_VEC, "01-------") then
                next_state <= 8;
            elsif (REQ_VEC(9) = '1') then
                next_state <= 0;   
            elsif REQ_VEC(8) = '0' then
                next_state <= 0;
            end if;
         WHEN 9 =>
            if REQ_VEC(9) = '1' then
                 next_state <= 9; 
            elsif REQ_VEC(9) = '0' then
                 next_state <= 0;
            end if;
   END CASE;
   
   END PROCESS state_logic;
   ----------------------------------------------------------------------------
   
   ----------------------------------------------------------------------------
   output_logic : PROCESS (current_state)
   ----------------------------------------------------------------------------
   BEGIN
   if current_state = 0 then
        ACK_VEC <= (others => '0');
   elsif current_state = 1 then
        ACK_VEC <= (1 => '1', others => '0');
   elsif current_state = 2 then
        ACK_VEC <= (2 => '1', others => '0');
   elsif current_state = 3 then
        ACK_VEC <= (3 => '1', others => '0');
   elsif current_state = 4 then
        ACK_VEC <= (4 => '1', others => '0');
   elsif current_state = 5 then
        ACK_VEC <= (5 => '1', others => '0');
   elsif current_state = 6 then
        ACK_VEC <= (6 => '1', others => '0');
   elsif current_state = 7 then
        ACK_VEC <= (7 => '1', others => '0');
   elsif current_state = 8 then
        ACK_VEC <= (8 => '1', others => '0');
   else
        ACK_VEC <= (9 => '1', others => '0');
   end if;
   -----------------------------
   
   END PROCESS output_logic;
   ----------------------------------------------------------------------------
   
END behav_priority;
