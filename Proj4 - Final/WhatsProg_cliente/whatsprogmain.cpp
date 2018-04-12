#include <QMessageBox>
#include <iostream>
#include <sstream>
#include "whatsprogmain.h"
#include "ui_whatsprogmain.h"
#include "modelconversas.h"
#include "modelmensagens.h"
#include "dados_cliente.h"
#include "socket_whatsprog.h"

using namespace std;

// Esta é a thread que recebe as informacoes do socket e
// armazena na variavel DCliente, de onde elas poderao ser
// exibidas pela interface visual

DWORD WINAPI le_msg(LPVOID lpParameter)
{
  while (s.connected()) {
    /*//Feito por sid >>>>
      //list<Mensagem> msg_ext;
      //string msg;

      //s.read_string(msg, TIMEOUT_WHATSPROG);//É assim que obtem as mensagens que estão no socket???
      //msg_ext.insert(msg);

      int comando;
      int id_msg;
      string remetente_msg;
      string texto_msg;
      s.read_int(comando, TIMEOUT_WHATSPROG);
      s.read_int(id_msg, TIMEOUT_WHATSPROG);
      s.read_string(remetente_msg, TIMEOUT_WHATSPROG); // esse formato de obter as variáveis está correta???
      s.read_string(texto_msg, TIMEOUT_WHATSPROG);
      switch(comando)
      {
        case CMD_NEW_USER:
            //Erro do servidor. Ignorar;
            break;
        case CMD_LOGIN_USER:
            //Erro do servidor. Ignorar;
            break;
        case CMD_LOGIN_OK:
            //Erro do servidor. Ignorar;
            break;
        case CMD_LOGIN_INVALIDO:
            //Erro do servidor. Ignorar;
            break;
        case CMD_NOVA_MSG:

            bool conversaExiste = false;
            int intConversaExiste;
            // tentar usar o metodo find função do STL Vector;
            for(int i = 0; i < DCliente.size();i++)
            {
                if(remetente_msg == DCliente[i].getCorrespondente())
                {

                    conversaExiste = true;
                    intConversaExiste = i;
                }
            }

            //Como preencher os dados de mensagem
            Mensagem newM;
            newM.setId(id_msg);
            newM.setRemetente(remetente_msg);
            newM.setDestinatario(DCliente.getMeuUsuario());
            newM.setTexto(texto_msg);




            if(conversaExiste)
            {
                // já existe a conversa, só adicionar a nova mensagem<CodCerto?>;
                if(DCliente[intConversaExiste].getCorrespondente() == remetente_msg)// Esse If será para o caso que está aberto na conversa<CodCorreto?>;
                {
                    newM.setStatus(MSG_LIDA);

                    s.write_int(CMD_MSG_LIDA1);
                    s.write_int(DCliente[intConversaExiste][DCliente[intConversaExiste].size() - 1].getId());
                    s.write_string(DCliente[intConversaExiste][DCliente[intConversaExiste].size() - 1].getRemetente()); // É assim que escreve informações no socket para o servidor ler???
                    //Ativar protocolo de envio de confirmação de visualização<CodCerto???>;
                }
                DCliente[intConversaExiste].insertMessage(newM);
            }else{
                newM.setStatus(MSG_ENTREGUE);
                DCliente.insertConversa(remetente_msg);
                DCliente[intConversaExiste].insertMessage(newM);

                // A conversa ainda não existe deve ser criada e adicionada a nova mensagem
            }
            break;
        case CMD_MSG_RECEBIDA:
            int id_msg2;
            s.read_int(id_msg2, TIMEOUT_WHATSPROG);
            //fazer um if verificando a ultima mensagem recebida da conversa em questão
            //if(id_msg2==id_)

            //Apenas 1% das vezes entrará no for
            for(int i = 0; i < DCliente.size();i++)
            {

            }
            break;
        case CMD_MSG_ENTREGUE:
            break;
        case CMD_MSG_LIDA1:
            break;
        case CMD_MSG_LIDA2:
            break;
        case CMD_MSG_INVALIDA :
            break;
        case CMD_ID_INVALIDA:
            break;
        case CMD_USER_INVALIDO:
            break;
        case CMD_MSG_INVALIDA:
            break;
        case CMD_LOGOUT_USER:
            break;
        default:
            break;


      }

      //Agora que tenho as mensagens, oque eu faço com elas? Adiciono ao DCliente???
    ///Feito por sid <<<<*/
  }
  return 0;
}

WhatsProgMain::WhatsProgMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WhatsProgMain)
{
    ui->setupUi(this);

    // A lista da esquerda (conversas)
    modelConversas = new ModelConversas(this);
    ui->tableViewConversas->setModel( modelConversas );
    ui->tableViewConversas->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableViewConversas->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableViewConversas->horizontalHeader()->setSectionsClickable(false);
    ui->tableViewConversas->setShowGrid(false);
    ui->tableViewConversas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewConversas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewConversas->setTabKeyNavigation(false);

    // A lista da direita (mensagens)
    modelMensagens = new ModelMensagens(this);
    ui->tableViewMensagens->setModel( modelMensagens );
    ui->tableViewMensagens->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableViewMensagens->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableViewMensagens->horizontalHeader()->setSectionsClickable(false);
    ui->tableViewMensagens->setShowGrid(true);
    ui->tableViewMensagens->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableViewMensagens->setTabKeyNavigation(false);

    // A barra de status
    statusBar()->insertWidget(0,new QLabel("SERVIDOR: "));
    if (DCliente.getServidor() == "")
    {
        ipServidor = new QLabel("---");
    }
    else
    {
        ipServidor = new QLabel(DCliente.getServidor().c_str());
    }
    statusBar()->insertWidget(1,ipServidor);

    statusBar()->insertWidget(2,new QLabel("   USUÁRIO: "));
    if (DCliente.getMeuUsuario() == "")
    {
        nomeUsuario = new QLabel("---");
    }
    else
    {
        nomeUsuario = new QLabel(DCliente.getMeuUsuario().c_str());
    }
    statusBar()->insertWidget(3,nomeUsuario);

    statusBar()->insertWidget(4,new QLabel("   CONVERSA: "));
    if (DCliente.getIdConversa() < 0)
    {
        nomeConversa = new QLabel("---");
    }
    else
    {
        nomeConversa = new QLabel(DCliente[DCliente.getIdConversa()].getCorrespondente().c_str());
    }
    statusBar()->insertWidget(5,nomeConversa);

    // A caixa de dialogo de login
    loginDialog = new LoginDialog(this);

    // As conexoes
    connect(this, SIGNAL (conversasModificada()),
            modelConversas, SLOT (slotAtualizaConversas()));
    connect(this, SIGNAL (numMsgConversaModificado(unsigned)),
            modelConversas, SLOT (slotAtualizaNumMsgConversa(unsigned)));
    connect(this, SIGNAL (mensagensModificada()),
            modelMensagens, SLOT (slotAtualizaMensagens()));
    connect(this, SIGNAL (statusModificada()),
            this, SLOT (slotAtualizaBarraStatus()));

    connect(loginDialog, SIGNAL (aceitaUsuario(const string, const string, const string, bool)),
            this, SLOT (slotAceitaUsuario(const string, const string, const string, bool)));
}

WhatsProgMain::~WhatsProgMain()
{
    delete ui;
}

void WhatsProgMain::slotAtualizaBarraStatus()
{
    if (DCliente.getServidor() == "")
    {
        ipServidor->setText("---");
    }
    else
    {
        ipServidor->setText(DCliente.getServidor().c_str());
    }

    if (DCliente.getMeuUsuario() == "")
    {
        nomeUsuario->setText("---");
    }
    else
    {
        nomeUsuario->setText(DCliente.getMeuUsuario().c_str());
    }

    if (DCliente.getIdConversa() < 0)
    {
        nomeConversa->setText("---");
    }
    else
    {
        nomeConversa->setText(DCliente[DCliente.getIdConversa()].getCorrespondente().c_str());
    }
}

void WhatsProgMain::slotAceitaUsuario(const string &IP, const string &login,
                                      const string &senha, bool novoUsuario )
{
    if (IP == "")
    {
        QMessageBox::warning(this, "Login", "IP inválido.");
        return;
    }
    if (login.size()<TAM_MIN_NOME_USUARIO || login.size()>TAM_MAX_NOME_USUARIO)
    {
        QMessageBox::warning(this, "Login", "Usuário inválido.");
        return;
    }
    if (login == DCliente.getMeuUsuario())
    {
        QMessageBox::warning(this, "Login", "Usuário já conectado.");
        return;
    }
    if (senha.size()<TAM_MIN_SENHA || senha.size()>TAM_MAX_SENHA)
    {
        QMessageBox::warning(this, "Login", "Senha inválida.");
        return;
    }

    // Desconecta o socket, encerra a thread de leitura de dados,
    // limpa o servidor e usuario atuais, limpa todas as conversas,
    // redesenha todas as janelas
    on_actionDesconectar_triggered();

    // Conecta o socket
    if (s.connect(IP.c_str(), PORTA_WHATSPROG) != SOCKET_OK)
    {
        string msg = "Impossivel conectar com servidor "+IP+" na porta "+PORTA_WHATSPROG;
        QMessageBox::warning(this, "Erro de conexão", msg.c_str());
        return;
    }

    // Envia a msg de conexao para o servidor, atraves do socket
    bool conexaoOK = true;
    if (novoUsuario)
    {
        // Testa se eh possivel cadastrar um novo usuario com esses ip, login e senha
        // Envia o comando CMD_NEW_USER
        if (conexaoOK) conexaoOK = (s.write_int(CMD_NEW_USER) != SOCKET_ERROR);
    }
    else
    {
        // Testa se eh possivel se conectar com esses ip, login e senha
        // Envia o comando CMD_LOGIN_USER
        if (conexaoOK) conexaoOK = (s.write_int(CMD_LOGIN_USER) != SOCKET_ERROR);
    }
    // Envia os parametros do comando (login, senha)
    if (conexaoOK) conexaoOK = (s.write_string(login) != SOCKET_ERROR);
    if (conexaoOK) conexaoOK = (s.write_string(senha) != SOCKET_ERROR);
    if (!conexaoOK)
    {
        QMessageBox::warning(this, "Erro de conexão", "Erro no envio da conexão.");
        return;
    }

    int32_t cmd;
    conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd));// recebe o comandoque vem do servidor // é == mesmo???
    /*
    char buf[10];
    // inteiro para string. Até 10 algarísmos.
    sprintf(buf, "%i", cmd);
    //stringstream scmd;
    //scmd << cmd;
    QMessageBox::warning(this, "cmd = ", buf);
    */
    if (conexaoOK) conexaoOK = (cmd == CMD_LOGIN_OK);
    if (!conexaoOK)
    {
        QMessageBox::warning(this, "Erro de conexão", "Erro na leitura da resposta à conexão.");
        return;
    }

    // Lanca a thread de leitura dos dados do socket
    // Cria a thread que escreve as mensagens recebidas
    tHandle = CreateThread(NULL, 0, le_msg, NULL , 0, NULL);
    if (tHandle == NULL)
    {
        s.close();
        QMessageBox::warning(this, "Erro de conexão", "Erro na criação da thread de leitura do socket.");
        return;
    }

    // Armazena o novo nome do servidor e do usuário
    DCliente.setServidorUsuario(IP,login);

    // Redesenha todas as janelas
    emit conversasModificada();
    emit mensagensModificada();
    emit statusModificada();

    // Informa que o novo usuario estah conectado
    QMessageBox::information(this, "Login", "Usuário conectado.");
}

void WhatsProgMain::on_actionNovo_triggered()
{
    loginDialog->setUsuario(true);
}

void WhatsProgMain::on_actionConectar_triggered()
{
    loginDialog->setUsuario(false);
}

// Desconecta o socket, encerra a thread de leitura de dados,
// limpa o servidor e usuario atuais, limpa todas as conversas,
// redesenha todas as janelas
void WhatsProgMain::on_actionDesconectar_triggered()
{
    if (s.connected())
    {
        // Envia o comando de logout
        s.write_int(CMD_LOGOUT_USER);
        // Fecha o socket e, consequentemente,
        // encerra a thread de leitura de dados do socket
        s.close();
    }

    // Limpa os nomes do servidor e usuario
    DCliente.clearServidorUsuario();

    // Redesenha todas as janelas
    emit conversasModificada();
    emit mensagensModificada();
    emit statusModificada();
}

void WhatsProgMain::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void WhatsProgMain::on_tableViewConversas_activated(const QModelIndex &index)
{
    on_tableViewConversas_clicked(index);
}

void WhatsProgMain::on_tableViewConversas_clicked(const QModelIndex &index)
{
    if (index.row() >= (int)DCliente.size())
    {
        cerr << "ID de conversa invalida.\n";
        return;
    }

    if (index.row() != DCliente.getIdConversa())
    {
        DCliente.setIdConversa(index.row());

        // Muda o status de todas as msgs que foram enviadas para mim de RECEBIDA -> LIDA
        bool houve_leitura = false;
        for (unsigned i=0; i<DCliente[DCliente.getIdConversa()].size(); i++)
        {
            if (DCliente[DCliente.getIdConversa()][i].getRemetente() == DCliente[DCliente.getIdConversa()].getCorrespondente() &&
                DCliente[DCliente.getIdConversa()][i].getStatus() == MSG_ENTREGUE)
            {
                DCliente[DCliente.getIdConversa()][i].setStatus(MSG_LIDA);
                // Envia msg ao servidor informando que a msg foi lida


                houve_leitura = true;
            }
        }
        if (houve_leitura)
        {
            emit numMsgConversaModificado(DCliente.getIdConversa());
        }

        // Sinaliza para atualizar a janela de mensagens e a barra de status
        emit mensagensModificada();
        emit statusModificada();
    }
}

void WhatsProgMain::on_lineEditMensagem_returnPressed()
{
    if (DCliente.getMeuUsuario().size() < TAM_MIN_NOME_USUARIO)
    {
        QMessageBox::warning(this, "Usuário inválido", "Usuário não definido.");
        return;
    }
    if (DCliente.getIdConversa()<0 || DCliente.getIdConversa()>=(int)DCliente.size())
    {
        QMessageBox::warning(this, "Conversa inválida", "Conversa não selecionada.");
        return;
    }
    string arg1 = ui->lineEditMensagem->text().toStdString();
    if (arg1.size()==0 || arg1.size()>TAM_MAX_MSG)
    {
        QMessageBox::warning(this, "Msg inválida", "Tamanho da mensagem inválido.");
        return;
    }
    ui->lineEditMensagem->clear();

    Mensagem M;
    // Define os campos da msg
    M.setId(DCliente.getNovaIdMensagem());
    // Nome do remetente
    M.setRemetente(DCliente.getMeuUsuario());
    // Nome do destinatario
    M.setDestinatario(DCliente[DCliente.getIdConversa()].getCorrespondente());
    // Texto da mensagem
    M.setTexto(arg1);
    // Estado (status) da mensagem
    M.setStatus(MSG_ENVIADA);

    // Envia a msg M via socket para o servidor

    // Inclui a msg na base de dados local

    // Acrescenta no final da conversa
    DCliente[DCliente.getIdConversa()].insertMessage(M);
    // Sinaliza que houve alteracao no numero de msgs de uma conversa na janela de conversas
    emit numMsgConversaModificado(DCliente.getIdConversa());
    // Sinaliza que houve alteracao na janela de Mensagens
    emit mensagensModificada();
}
