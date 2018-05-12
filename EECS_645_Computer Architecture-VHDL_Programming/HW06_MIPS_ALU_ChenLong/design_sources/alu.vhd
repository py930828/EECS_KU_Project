LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
USE work.my_package.ALL;
USE work.math_real.ALL;
USE ieee.numeric_std.ALL;

ENTITY ALU IS
   PORT( 
      A           : IN     std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
      ALU_control : IN     std_logic_vector (n_bits_of(n_functions_alu) - 1 DOWNTO 0);
      B           : IN     std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
      C           : OUT    std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
      zero        : OUT    std_logic;
      overflow    : OUT    std_logic
   );
END ALU;


ARCHITECTURE behav OF ALU IS

   -- Internal signal declarations
   SIGNAL ALU_control_int : natural RANGE 0 TO (n_functions_alu - 1);
   SIGNAL A_internal : std_logic_vector(n_bits_alu DOWNTO 0);
   SIGNAL B_internal : std_logic_vector(n_bits_alu DOWNTO 0);
   SIGNAL C_internal : std_logic_vector(n_bits_alu DOWNTO 0);
   SIGNAL s_A, s_B, s_C : std_logic; -- Sign bits of A, B, C

BEGIN
   
   --- insert your code here ---
    process( ALU_control )
    begin
        ALU_control_int <= to_integer(unsigned(ALU_control));
        A_internal <= '0' & A;
        B_internal <= '0' & B;
        s_A <= A(n_bits_alu-1);
        s_B <= B(n_bits_alu-1);
    end process;
    
    process( ALU_control_int, A_internal, B_internal )
    begin
        if (ALU_control_int = 0) then  -- C = A and B
           for I in 0 to n_bits_alu loop
                C_internal(I) <= A_internal(I) and B_internal(I);
           end loop;
           overflow <= '0';
        elsif (ALU_control_int = 1) then  -- C = A or B
            for I in 0 to n_bits_alu loop
                        C_internal(I) <= A_internal(I) or B_internal(I);
            end loop;
            overflow <= '0';
        elsif (ALU_control_int = 2) then   -- C = A + B
            C_internal <= A_internal + B_internal;
            if( s_A = '0' and s_B = '0' ) then
                overflow <= C_internal(n_bits_alu);
            else
                if ( C_internal(n_bits_alu) = C_internal(n_bits_alu-1) ) then
                    overflow <= '1';
                else
                    overflow <= '0';
                end if;
             end if;
        elsif (ALU_control_int = 6) then   -- C = A - B
             C_internal <= A_internal - B_internal;
             if( s_A = '0' and s_B = '0' ) then
                 overflow <= C_internal(n_bits_alu);
             else
                 if ( C_internal(n_bits_alu) = C_internal(n_bits_alu-1) ) then
                     overflow <= '1';
                 else
                     overflow <= '0';
                 end if;
              end if;
         elsif (ALU_control_int = 7 ) then  --C = 1 when(A < B) else 0
            if (A_internal < B_internal ) then
                C_internal <= (n_bits_alu downto 1 => '0') & '1' ;
            else
                C_internal <= (others => '0');
            end if;
            overflow <= '0';
         elsif (ALU_control_int = 12) then
            for I in 0 to n_bits_alu loop
                 C_internal(I) <= A_internal(I) nor B_internal(I);
            end loop;
            overflow <= '0';
         else
            C_internal <= (others => '0');
         end if;
    end process;
    
    C <= C_internal( n_bits_alu-1 downto 0);
    zero <= '1' when C_internal = 0 else
            '0';
    
END behav;
