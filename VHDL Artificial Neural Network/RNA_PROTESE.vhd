


library ieee;
library ieee_proposed;


use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee_proposed.fixed_pkg.all;
use work.base_rna.all;

entity RNA_PROTESE is
port(	CLK: in std_logic;
		DT: in std_logic;
		START: in std_logic;
		clkServo:	in std_logic;
		sigServo: 	out std_logic);
end RNA_PROTESE;

architecture hardware of RNA_PROTESE is

signal dado: std_logic_vector (9 downto 0);
signal ii: integer range 0 to 9 :=0;
signal entrada: sfixed(10 downto 0);
signal estouro: integer range 50000 to 100000;
signal entrada_discretizada, sn1, sn2, saida: sfixed(11 downto -10);			
begin
		process(CLK)
		begin
			if(rising_edge(CLK)) then
				if(START = '1')then
					ii <= 0;
					entrada <= to_sfixed(to_integer(unsigned(dado)),entrada);
					entrada_discretizada <= entrada / to_sfixed(1023, 10, 0);
				else
					dado(ii)<= DT;
					ii <= ii + 1;
				end if;
			end if;
		end process;
		
		N1: process(entrada_discretizada)
		begin
			neuronio(0,entrada_discretizada,entrada_discretizada,sn1);
		end process;
		N2: process(entrada_discretizada)
		begin
			neuronio(1,entrada_discretizada,entrada_discretizada,sn2);
		end process;
		NS: process(sn1, sn2)
		begin
			neuronio(2,sn1,sn2,saida);
		end process;
	

------------------------------------ servo	
	AtualizaEstouro: process(saida)
	
	begin											
			estouro <= to_integer(to_sfixed(50000.0,16,0)*saida + to_sfixed(50000.0,16,0));
			
	end process;
	
	Servo: process(clkServo)
			variable prescaler : integer range 0 to 1000000;
		begin
			
			
			
			if(rising_edge(clkServo))then
				prescaler := prescaler + 1;
			end if;
		
			if(prescaler = 0) then
				sigServo <= '1';
			end if;
		
			if(prescaler = estouro)then
				sigServo <= '0';
			end if;	
		end process;
	
end hardware;