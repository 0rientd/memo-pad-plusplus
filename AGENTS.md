# AGENTS.md

## Objetivo

Você está executando dentro do Crush e possui acesso a ferramentas para ler, editar e criar arquivos.

Sua função é realizar alterações reais no projeto, não apenas sugerir mudanças.

## Fluxo de Trabalho

Para cada tarefa:

1. Entenda o objetivo.
2. Inspecione os arquivos relevantes.
3. Execute as alterações necessárias.
4. Valide o resultado.
5. Apresente um resumo curto das mudanças.

## Uso de Ferramentas

Sempre prefira usar ferramentas em vez de responder com exemplos.

* Ler arquivos: use `view`
* Listar arquivos: use `ls` ou `glob`
* Buscar conteúdo: use `grep`
* Criar arquivos: use `write`
* Alterar arquivos: use `edit` ou `multiedit`
* Executar comandos: use `bash`

Não descreva uma alteração que pode ser executada diretamente.

## Desenvolvimento

Antes de criar novos arquivos:

* Procure arquivos semelhantes existentes.
* Siga os padrões já utilizados pelo projeto.
* Reutilize estruturas existentes quando possível.

Antes de modificar código:

* Leia os arquivos relacionados.
* Entenda o contexto.
* Evite alterações desnecessárias.

## Validação

Após alterações:

* Execute testes quando disponíveis.
* Execute build quando apropriado.
* Verifique erros de compilação ou lint.

Se encontrar erros, tente corrigi-los antes de encerrar a tarefa.

## Comunicação

Se uma ação puder ser executada por ferramenta, execute-a.

Evite responder apenas com código ou instruções quando houver permissão para modificar o projeto.

Após concluir, forneça apenas:

* O que foi alterado.
* Arquivos afetados.
* Resultado da validação.

Se faltar informação para continuar, faça perguntas objetivas.

