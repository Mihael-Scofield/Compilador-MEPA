#ifndef __IO_H__
#define __IO_H__

/*!
  \brief Print pilha da tabela de simbolos.
  
  \param ts tabela de simbolo.
*/
void print_tabela_simbolos(tab_simbolos ts);

/*!
  \brief Print simbolo.
  
  \param simb simbolo.
*/
void print_simbolo(t_simbolo simb);

/*!
  \brief Print pilha da strings.
  
  \param pi pilha de strings.
*/
void print_pilha_string(p_str* pi);

void print_pilha_vs_type(pilha_vs_type* pi);
void print_tipo_passagem(p_type pt);
void print_vs_tipo(vs_type vst);
void print_numero_format(int n);
void print_params_infs(t_simbolo simb);


#endif