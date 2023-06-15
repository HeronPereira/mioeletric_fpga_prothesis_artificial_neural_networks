

library ieee;
library ieee_proposed;


use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee_proposed.fixed_pkg.all;
--use ieee.math_real.all;

package base_rna is
	
	procedure neuronio(constant id: in integer; signal entrada1,entrada2: in sfixed(11 downto -10); signal saida: out sfixed(10 downto -14)) ;
end base_rna;		

--
--entity neuronio is
--	port( entrada1: in sfixed(5 downto -14);
--			entrada2: in sfixed(5 downto -14);
--			id: in integer;
--			saida: out sfixed(5 downto -14));
--end neuronio;

--architecture hardware of neuronio is
--		
--		type vetor is array (0 to 8) of sfixed(5 downto -14);
--		signal net: sfixed(12 downto -21);
--		signal resultado: sfixed(11 downto -21);
--		
--		variable pesos_sinapticos : vetor := (to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10), to_sfixed(1,11, -10));
--
--begin
--		process(entrada1, entrada2, id)
package body base_rna is		
		
		procedure neuronio(variable id: in integer; signal entrada1,entrada2: in sfixed(11 downto -10); signal saida: out sfixed(11 downto -10)) is

			type vetor is array (0 to 6) of sfixed(7 downto -14);
			variable net: sfixed(21 downto -24);
			variable mult1, mult2: sfixed(19 downto -24);


			variable pesos_sinapticos : vetor := (to_sfixed(35.716431,7, -14), --w1n1
															  to_sfixed(-0.521039,7, -14),--bias1
															  to_sfixed(-38.648618,7, -14),--w1n2
															  to_sfixed(8.777158,7, -14),--bias2
															  to_sfixed(7.372067,7, -14),--w1n3
															  to_sfixed(-14.271796,7, -14),--w2n3
															  to_sfixed(7.486531,7, -14));--bias3
		
			begin
				if(id = 0)then																												---	Conforme o valor do id irá gerar a resposta de um neuronio diferente
					--Utilizar o resize
					mult1 := entrada1*pesos_sinapticos(0);
					net := mult1 + pesos_sinapticos(1)+0;

				elsif (id = 1)then
					
					mult1 := entrada1*pesos_sinapticos(2);
					net := mult1 + pesos_sinapticos(3)+0;
					

				elsif (id = 2)then
					mult1 := entrada1*pesos_sinapticos(4);
					mult2 := entrada2*pesos_sinapticos(5);
					net := mult1 + mult2 + pesos_sinapticos(6);
					
					--net := resize(entrada1*pesos_sinapticos(6)+entrada2*pesos_sinapticos(7)+pesos_sinapticos(8),21, -24);		--		Se for 0 é o primeiro neuronio que possui o peso 6 e 7 e o primeiro bias (8) que será só ele pelo bias ser 1
		--			resultado <= 1/(1+log(net));
				end if;
				
		------------Procura o resultado na função sigmoide discretizada
				if (net < to_sfixed(-4.1,21, -24)) then
				
					saida <= to_sfixed(0.01,11, -10);
					
				elsif(net >= to_sfixed(-4.1,21, -24) and net < to_sfixed(-3.6,21, -24)) then
				
					saida <= to_sfixed(0.02,11, -10);
					
				elsif(net >= to_sfixed(-3.6,21, -24) and net < to_sfixed(-3.3,21, -24)) then
				
					saida <= to_sfixed(0.03,11, -10);
					
				elsif(net >= to_sfixed(-3.3,21, -24) and net < to_sfixed(-3.0,21, -24)) then
				
					saida <= to_sfixed(0.04,11, -10);
					
				elsif(net >= to_sfixed(-3.0,21, -24) and net < to_sfixed(-2.8,21, -24)) then
				
					saida <= to_sfixed(0.05,11, -10);
					
				elsif(net >= to_sfixed(-2.8,21, -24) and net < to_sfixed(-2.6,21, -24)) then
				
					saida <= to_sfixed(0.06,11, -10);
					
				elsif(net >= to_sfixed(-2.6,21, -24) and net < to_sfixed(-2.5,21, -24)) then
				
					saida <= to_sfixed(0.07,11, -10);
					
				elsif(net >= to_sfixed(-2.5,21, -24) and net < to_sfixed(-2.3,21, -24)) then
				
					saida <= to_sfixed(0.08,11, -10);
					
				elsif(net >= to_sfixed(-2.3,21, -24) and net < to_sfixed(-2.2,21, -24)) then
				
					saida <= to_sfixed(0.09,11, -10);
					
				elsif(net >= to_sfixed(-2.2,21, -24) and net < to_sfixed(-2.1,21, -24)) then
				
					saida <= to_sfixed(0.10,11, -10);
					
				elsif(net >= to_sfixed(-2.1,21, -24) and net < to_sfixed(-2.0,21, -24)) then
				
					saida <= to_sfixed(0.11,11, -10);
					
				elsif(net >= to_sfixed(-2.0,21, -24) and net < to_sfixed(-1.9,21, -24)) then
				
					saida <= to_sfixed(0.12,11, -10);
					
				elsif(net >= to_sfixed(-1.9,21, -24) and net < to_sfixed(-1.8,21, -24)) then
				
					saida <= to_sfixed(0.13,11, -10);
					
				elsif(net >= to_sfixed(-1.8,21, -24) and net < to_sfixed(-1.7,21, -24)) then
				
					saida <= to_sfixed(0.14,11, -10);
					
				elsif(net >= to_sfixed(-1.7,11, -10) and net < to_sfixed(-1.6,21, -24)) then
				
					saida <= to_sfixed(0.15,11, -10);
					
				elsif(net >= to_sfixed(-1.6,21, -24) and net < to_sfixed(-1.5,21, -24)) then
				
					saida <= to_sfixed(0.17,11, -10);
					
				elsif(net >= to_sfixed(-1.5,21, -24) and net < to_sfixed(-1.4,21, -24)) then
				
					saida <= to_sfixed(0.18,11, -10);
					
				elsif(net >= to_sfixed(-1.4,21, -24) and net < to_sfixed(-1.3,21, -24)) then
				
					saida <= to_sfixed(0.20,11, -10);
					
				elsif(net >= to_sfixed(-1.3,21, -24) and net < to_sfixed(-1.2,21, -24)) then
				
					saida <= to_sfixed(0.21,11, -10);
					
				elsif(net >= to_sfixed(-1.2,21, -24) and net < to_sfixed(-1.1,21, -24)) then
				
					saida <= to_sfixed(0.23,11, -10);
					
				elsif(net >= to_sfixed(-1.1,21, -24) and net < to_sfixed(-1.0,21, -24)) then
				
					saida <= to_sfixed(0.25,11, -10);
					
				elsif(net >= to_sfixed(-1.0,21, -24) and net < to_sfixed(-0.9,21, -24)) then
				
					saida <= to_sfixed(0.27,11, -10);
					
				elsif(net >= to_sfixed(-0.9,21, -24) and net < to_sfixed(-0.8,21, -24)) then
				
					saida <= to_sfixed(0.29,11, -10);
					
				elsif(net >= to_sfixed(-0.8,21, -24) and net < to_sfixed(-0.7,21, -24)) then
				
					saida <= to_sfixed(0.31,11, -10);
					
				elsif(net >= to_sfixed(-0.7,21, -24) and net < to_sfixed(-0.6,21, -24)) then
				
					saida <= to_sfixed(0.33,11, -10);
					
				elsif(net >= to_sfixed(-0.6,21, -24) and net < to_sfixed(-0.5,21, -24)) then
				
					saida <= to_sfixed(0.35,11, -10);
					
				elsif(net >= to_sfixed(-0.5,21, -24) and net < to_sfixed(-0.4,21, -24)) then
				
					saida <= to_sfixed(0.38,11, -10);
					
				elsif(net >= to_sfixed(-0.4,21, -24) and net < to_sfixed(-0.3,21, -24)) then
				
					saida <= to_sfixed(0.40,11, -10);
					
				elsif(net >= to_sfixed(-0.3,21, -24) and net < to_sfixed(-0.2,21, -24)) then
				
					saida <= to_sfixed(0.43,11, -10);
					
				elsif(net >= to_sfixed(-0.2,21, -24) and net < to_sfixed(-0.1,21, -24)) then
				
					saida <= to_sfixed(0.45,11, -10);
					
				elsif(net >= to_sfixed(-0.1,21, -24) and net < to_sfixed(0.0,21, -24)) then
				
					saida <= to_sfixed(0.48,11, -10);
					
				elsif(net >= to_sfixed(0.0,21, -24) and net < to_sfixed(0.1,21, -24)) then
				
					saida <= to_sfixed(0.5,11, -10);
					
				elsif(net >= to_sfixed(0.1,21, -24) and net < to_sfixed(0.2,21, -24)) then
				
					saida <= to_sfixed(0.52,11, -10);
					
				elsif(net >= to_sfixed(0.2,21, -24) and net < to_sfixed(0.3,21, -24)) then
				
					saida <= to_sfixed(0.55,11, -10);
					
				elsif(net >= to_sfixed(0.3,21, -24) and net < to_sfixed(0.4,21, -24)) then
				
					saida <= to_sfixed(0.57,11, -10);
					
				elsif(net >= to_sfixed(0.4,21, -24) and net < to_sfixed(0.5,21, -24)) then
				
					saida <= to_sfixed(0.60,11, -10);
					
				elsif(net >= to_sfixed(0.5,21, -24) and net < to_sfixed(0.6,21, -24)) then
				
					saida <= to_sfixed(0.62,11, -10);
					
				elsif(net >= to_sfixed(0.6,21, -24) and net < to_sfixed(0.7,21, -24)) then
				
					saida <= to_sfixed(0.65,11, -10);
					
				elsif(net >= to_sfixed(0.7,21, -24) and net < to_sfixed(0.9,21, -24)) then
				
					saida <= to_sfixed(0.70,11, -10);
					
				elsif(net >= to_sfixed(0.9,21, -24) and net < to_sfixed(1.0,21, -24)) then
				
					saida <= to_sfixed(0.71,11, -10);
					
				elsif(net >= to_sfixed(1.0,21, -24) and net < to_sfixed(1.1,21, -24)) then
				
					saida <= to_sfixed(0.73,11, -10);
					
				elsif(net >= to_sfixed(1.1,21, -24) and net < to_sfixed(1.2,21, -24)) then
				
					saida <= to_sfixed(0.75,11, -10);
					
				elsif(net >= to_sfixed(1.2,21, -24) and net < to_sfixed(1.3,21, -24)) then
				
					saida <= to_sfixed(0.77,11, -10);
					
				elsif(net >= to_sfixed(1.3,21, -24) and net < to_sfixed(1.4,21, -24)) then
				
					saida <= to_sfixed(0.78,11, -10);
					
				elsif(net >= to_sfixed(1.4,21, -24) and net < to_sfixed(1.5,21, -24)) then
				
					saida <= to_sfixed(0.80,11, -10);
					
				elsif(net >= to_sfixed(1.5,21, -24) and net < to_sfixed(1.6,21, -24)) then
				
				
					saida <= to_sfixed(0.82,11, -10);
					
				elsif(net >= to_sfixed(1.6,21, -24) and net < to_sfixed(1.7,21, -24)) then
				
					saida <= to_sfixed(0.83,11, -10);
					
				elsif(net >= to_sfixed(1.7,21, -24) and net < to_sfixed(1.8,21, -24)) then
				
					saida <= to_sfixed(0.85,11, -10);
					
				elsif(net >= to_sfixed(1.8,21, -24) and net < to_sfixed(1.9,21, -24)) then
				
					saida <= to_sfixed(0.86,11, -10);
					
				elsif(net >= to_sfixed(1.9,21, -24) and net < to_sfixed(2.0,21, -24)) then
				
					saida <= to_sfixed(0.87,11, -10);
					
				elsif(net >= to_sfixed(2.0,21, -24) and net < to_sfixed(2.1,21, -24)) then
				
					saida <= to_sfixed(0.88,11, -10);
					
				elsif(net >= to_sfixed(2.1,21, -24) and net < to_sfixed(2.2,21, -24)) then
				
					saida <= to_sfixed(0.89,11, -10);
					
				elsif(net >= to_sfixed(2.2,21, -24) and net < to_sfixed(2.3,21, -24)) then
				
					saida <= to_sfixed(0.90,11, -10);
					
				elsif(net >= to_sfixed(2.3,21, -24) and net < to_sfixed(2.4,21, -24)) then
				
					saida <= to_sfixed(0.91,11, -10);
					
				elsif(net >= to_sfixed(2.4,21, -24) and net < to_sfixed(2.6,21, -24)) then
				
					saida <= to_sfixed(0.92,11, -10);
					
				elsif(net >= to_sfixed(2.6,21, -24) and net < to_sfixed(2.7,21, -24)) then
				
					saida <= to_sfixed(0.93,11, -10);
					
				elsif(net >= to_sfixed(2.7,21, -24) and net < to_sfixed(2.9,21, -24)) then
				
					saida <= to_sfixed(0.94,11, -10);
					
				elsif(net >= to_sfixed(2.9,21, -24) and net < to_sfixed(3.1,21, -24)) then
				
					saida <= to_sfixed(0.95,11, -10);
					
				elsif(net >= to_sfixed(3.1,21, -24) and net < to_sfixed(3.4,21, -24)) then
				
					saida <= to_sfixed(0.96,11, -10);
					
				elsif(net >= to_sfixed(3.4,21, -24) and net < to_sfixed(3.7,21, -24)) then
				
					saida <= to_sfixed(0.97,11, -10);
					
				elsif(net >= to_sfixed(3.7,11, -10) and net < to_sfixed(4.3,11, -10)) then
				
					saida <= to_sfixed(0.98,11, -10);
					
				elsif(net >= to_sfixed(4.3,11, -10)) then
				
					saida <= to_sfixed(0.99,11, -10);
									
				end if;
				
			end neuronio;	
end package body;
--		end process;
--end hardware;