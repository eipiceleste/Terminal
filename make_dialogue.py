import struct
import json


dialogue_json = {
    "nodes": [
        {
            "id": 0,
            "text": "19 DE OUTUBRO DE 2077 - LOG 1\n\n[VOZ ELETRONICA] O seu aluguel esta em atraso, por favor pague o valor devido, voce tem ate o dia DEZENOVE. de. OUTUBRO.\n\n???: Que vidinha merda..\n\nA garota se levanta e dirige-se ao Cyberdeck, passando pela porta deslizante do seu quarto. Senta-se na cadeira.\n\nTELA DE LOGIN:\nUsuario: [INSIRA NOME]\nSenha: **\n\n[VOZ ELETRONICA] Bem vinda [NOME], o seu saldo atual e de 100€D",
            "options": [
                {"text": "[Inserir nome e continuar]", "next": 1, "minigame": 0},
                {"text": "[Sair do sistema]", "next": 0, "minigame": 0}
            ]
        },
        {
            "id": 1,
            "text": "???: Mas que caralhos? Ontem mesmo eu tinha o dinheiro do aluguel!\n\n(Pensamento) Ah.. deve ter sido o plano funerario.\n\nDesde que a mame morreu, as coisas por aqui tem sido dificeis.. quer dizer, nada nunca foi facil para nos.\n\nMalditos, prestam aquele servico porco e ainda cobram o olho da cara.\n\nA protagonista repousa a mao sob os olhos. Expressao cansada, quase melancolica.\n\n*BIP* Notificacao no holograma.",
            "options": [
                {"text": "Deve ser o resultado dos exames da semana passada...", "next": 2, "minigame": 0},
                {"text": "Ignorar notificacao", "next": 1, "minigame": 0}
            ]
        },
        {
            "id": 2,
            "text": "Ela clica na notificacao. Expandindo o arquivo medico.\n\n=================================\nPACIENTE: [NOME]\nEXAMES NEURAIS - RESULTADOS\nDIAGNOSTICO: DEGENERACAO CIBERNETICA\nESTAGIO: TERMINAL\nPROGNOSTICO: 6 MESES\n=================================\n\n???: Era so o que me faltava..\n\n*BIP-BIP* Nova notificacao. E-mail.",
            "options": [
                {"text": "Verificar e-mail", "next": 3, "minigame": 0},
                {"text": "Ignorar e-mail", "next": 2, "minigame": 0}
            ]
        },
        {
            "id": 3,
            "text": "E-MAIL RECEBIDO:\nREMETENTE: [CRIPTOGRAFADO]\nASSUNTO: URGENTE - SIGNO: COELHO\nPRIORIDADE: ALTA\n\nARQUIVO ANEXO: dados.pandora (CRIPTOGRAFADO NIVEL 3)\n\nMENSAGEM:\n\"Ela sabia. Sua mae sabia do Projeto Looking Glass.\nOs exames nao sao aleatorios. Sua doenca e projeto.\nEstao apagando voce. Como apagaram ela.\n\nProcure o Pais das Maravilhas.\nSiga o Coelho.\n\n\"",
            "options": [
                {"text": "Tentar descriptografar remetente", "next": -1, "minigame": 1},
                {"text": "Fechar e-mail (ignorar)", "next": 3, "minigame": 0}
            ]
        },
        {
            "id": 4,
            "text": "[APOS MINIGAME BEM-SUCEDIDO]\n\nREMENTENTE DESCRIPTOGRAFADO: alice@wonderland.onion\n\n???: Alice... O codinome da mae.\n\nNovo e-mail automatico:\n\"Bem-vinda ao buraco do coelho.\n\nSua mae trabalhou no Projeto Looking Glass.\nDescobriram como apagar memorias via implantes.\nSua 'doenca' e um wipe progressivo.\n\nEncontre-me no Pais das Maravilhas.\nCoordenadas: Club Neon, Downtown.\nSenha: 'O Coelho esta atrasado.'\n\nSobreviva. - Q\"\n\n*PISTA ADQUIRIDA: Local do Pais das Maravilhas*",
            "options": [
                {"text": "Continuar (6 dias depois)...", "next": 5, "minigame": 0}
            ]
        },
        {
            "id": 5,
            "text": "25 DE OUTUBRO DE 2077 - LOG 2\n\n[VOZ ELETRONICA] Voce possui UMA nova notificacao ALICE\n\nALICE: Abra o correio de voz, preciso de detalhes sobre meu primeiro alvo. Tomara que o Chapeleiro seja breve dessa vez, se deixar ele falando aquela matraca nao fecha nunca.\n\nA garota aperta um botao no smartphone. A notificacao toca no Cyberdeck.\n\nVoz adulterada com filtros ecoa...",
            "options": [
                {"text": "Ouvir mensagem do Chapeleiro", "next": 6, "minigame": 0}
            ]
        },
        {
            "id": 6,
            "text": "CHAPELEIRO/MADH4TT3R: Bom dia, boa tarde ou quem sabe boa noite, Alice! Espero que esta 'carta' lhe encontre bem. O Coelho avisou-me que o relogio corre rapidamente e portanto nao teremos muito mais tempo para alvos de menor prioridade.\n\nAs fofocas correm rapido no Pais das Maravilhas. Um grupo de Netrunners proximos informou-nos que o banco de dados da Rainha Vermelha esta em movimento. Eles buscam salvaguardar sua pesquisa trancafiando-a na Old net.\n\nAlgo que certamente nao pode nos escapar. A carga talvez contenha o que precisamos para trazer aqueles engomadinhos ao chao.\n\nConto com voce para descriptografar a chave de acesso. Um beijao Xuxu!\n\n[ANEXO: chave_rainha_vermelha.crypto]",
            "options": [
                {"text": "Examinar anexo", "next": 7, "minigame": 0}
            ]
        },
        {
            "id": 7,
            "text": "ALICE: Ele so pode estar de sacanagem, atacar a Rainha Vermelha logo agora??\n\n(Nao que eu tenha muita escolha sobre isso)\n\nComentou para si mesma em pensamento. A noticia subita fez a jovem saltar da cama. Imediatamente afastou os cabelos para revelar um plug em sua nuca.\n\nConectou um cabo para fazer interface com o Cyberdeck. Comecou o processo de mergulho.\n\nCONSCIENCIA TRANSFERIDA PARA O MUNDO DIGITAL...",
            "options": [
                {"text": "Iniciar hack (Jogo de Cartas vs Rainha Vermelha)", "next": -1, "minigame": 1}
            ]
        },
        {
            "id": 8,
            "text": "[APOS VENCER MINIGAME DE CARTAS]\n\nCHAVE DE CRIPTOGRAFIA OBTIDA!\n\nArquivo anexo descriptografado:\n\n\"LOCAL DO BANCO DE DADOS: SERVIDOR 7, TORRE UMBRELLA\nFIREWALLS: 5 CAMADAS (ICE)\nTEMPO ESTIMADO DE PENETRACAO: 120 SEGUNDOS\n\nBOA SORTE, ALICE. NAO SE DEIXE PEGAR.\n- CHAPELEIRO\"\n\n*PISTA ADQUIRIDA: Localizacao do banco de dados*",
            "options": [
                {"text": "Invasao: Quebrar firewalls (Button Mashing)", "next": -1, "minigame": 2},
                {"text": "Retornar ao mundo real (arriscado)", "next": 9, "minigame": 0}
            ]
        },
        {
            "id": 9,
            "text": "[SE FALHAR NO BUTTON MASHING]\n\nALERTA: FIREWALL DETECTOU INTRUSAO!\n\nICE ATIVADO. RASTREANDO CONEXAO...\nCONEXAO INTERROMPIDA FORCADAMENTE.\n\nVOCE FOI PEGA.\n\n[VOZ DA RAINHA VERMELHA] Encontramos voce, coelhina. Venha brincar conosco...\n\n=== GAME OVER ===",
            "options": [
                {"text": "Tentar novamente", "next": 7, "minigame": 0},
                {"text": "Voltar ao menu principal", "next": -1, "minigame": 0}
            ]
        },
        {
            "id": 10,
            "text": "[SE VENCER BUTTON MASHING]\n\nFIREWALLS QUEBRADOS!\n\nACESSO CONCEDIDO AO BANCO DE DADOS DA RAINHA VERMELHA.\n\nARQUIVOS ENCONTRADOS:\n- projeto_looking_glass_fase3.pdf\n- lista_agentes_comprometidos.txt\n- protocolo_apagamento_neural.doc\n\nDOWNLOAD INICIADO... 45%\n\nCHAPELEIRO: Excelente trabalho, Alice! Saia de la antes que...\n\nALERTA: DRONES DE SEGURANCA ACIONADOS!",
            "options": [
                {"text": "Continuar download (arriscado)", "next": 11, "minigame": 0},
                {"text": "Sair imediatamente", "next": 12, "minigame": 0}
            ]
        },
        {
            "id": 11,
            "text": "DOWNLOAD COMPLETO 100%\n\nARQUIVOS SALVOS LOCALMENTE.\n\nALICE: Consegui! Agora vaza daqui...\n\nDRONES APROXIMANDO. CONEXAO INSTAVEL.\n\nCORRIDA DIGITAL CONTRA O TEMPO...\n\nDESCONEXAO FORCADA. VOCE ACORDA NO SEU QUARTO.\n\nRESPIRANDO PESADO. SUANDO FRIO.\n\nMAS OS ARQUIVOS ESTAO COM VOCE.\n\n=== MISSÃO CONCLUÍDA ===",
            "options": [
                {"text": "Continuar historia", "next": 13, "minigame": 0}
            ]
        }
    ]
}

MAX_LENGTH = 1024  # Define no topo

def create_binary():
    with open('data/dialogue.dat', 'wb') as f:
        f.write(struct.pack('i', len(dialogue_json['nodes'])))
        
        for node in dialogue_json['nodes']:
            f.write(struct.pack('i', node['id']))
            
            text = node['text'].encode('utf-8')
            padded = text.ljust(MAX_LENGTH, b'\0')[:MAX_LENGTH]
            f.write(padded)
            
            f.write(struct.pack('i', len(node['options'])))
            
            for opt in node['options']:
                opt_text = opt['text'].encode('utf-8')
                padded_opt = opt_text.ljust(MAX_LENGTH, b'\0')[:MAX_LENGTH]
                f.write(padded_opt)
                f.write(struct.pack('i', opt['next']))
                f.write(struct.pack('i', opt['minigame']))
    
    print(f"Arquivo binário criado: {len(dialogue_json['nodes'])} nós")

if __name__ == "__main__":
    create_binary()