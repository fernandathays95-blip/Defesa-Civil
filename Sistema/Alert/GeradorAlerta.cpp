#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Para system()

using namespace std;

// Nome do arquivo que simula a publicação do alerta.
const string ARQUIVO_ALERTA = "alerta_vigente.txt";

void mostrar_alerta_atual() {
    ifstream arquivo(ARQUIVO_ALERTA);
    string linha;

    cout << "------------------------------------------" << endl;
    cout << "  ALERTA ATUAL (AlertaVigente.txt):" << endl;
    cout << "------------------------------------------" << endl;

    if (arquivo.is_open()) {
        if (getline(arquivo, linha) && !linha.empty()) {
            cout << ">>> " << linha << endl;
        } else {
            cout << "NENHUM ALERTA ATIVO." << endl;
        }
        arquivo.close();
    } else {
        cout << "NENHUM ALERTA ATIVO (Arquivo nao encontrado)." << endl;
    }
    cout << "------------------------------------------" << endl;
}

void publicar_alerta() {
    string mensagem;
    cout << "\n--- PUBLICAR NOVO ALERTA ---\n";
    cout << "Digite a mensagem de alerta EXTREMO: ";
    
    // Para ler a linha inteira, incluindo espaços
    cin.ignore(); 
    getline(cin, mensagem);
    
    if (mensagem.empty()) {
        cout << "❌ Mensagem vazia. Publicação cancelada." << endl;
        return;
    }

    // Salva a mensagem no arquivo
    ofstream arquivo_saida(ARQUIVO_ALERTA);
    if (arquivo_saida.is_open()) {
        arquivo_saida << mensagem << endl;
        arquivo_saida.close();
        cout << "\n✅ ALERTA PUBLICADO COM SUCESSO!" << endl;
    } else {
        cerr << "\n❌ ERRO: Nao foi possivel escrever no arquivo " << ARQUIVO_ALERTA << endl;
    }
}

void encerrar_alerta() {
    if (remove(ARQUIVO_ALERTA.c_str()) == 0) {
        cout << "\n✅ ALERTA ENCERRADO E ARQUIVO REMOVIDO COM SUCESSO!" << endl;
    } else {
        cerr << "\n⚠️ Nao havia alerta ativo ou erro ao tentar remover o arquivo." << endl;
    }
}

int main() {
    int opcao;

    while (true) {
        // Limpa a tela para o menu
        system("clear");
        
        cout << "===============================================" << endl;
        cout << "  SISTEMA C++ DE ALERTA - DEFESA CIVIL" << endl;
        cout << "===============================================" << endl;

        mostrar_alerta_atual();

        cout << "\nOPÇÕES:" << endl;
        cout << "1. Publicar Novo Alerta" << endl;
        cout << "2. Encerrar Alerta" << endl;
        cout << "3. Sair" << endl;
        cout << "-----------------------------------------------" << endl;
        
        cout << "Escolha uma opcao (1-3): ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                publicar_alerta();
                break;
            case 2:
                encerrar_alerta();
                break;
            case 3:
                cout << "Saindo do Sistema..." << endl;
                return 0;
            default:
                cout << "Opcao invalida. Pressione Enter para tentar novamente." << endl;
                cin.ignore();
                cin.get();
                break;
        }
        cout << "\nPressione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    return 0;
}
