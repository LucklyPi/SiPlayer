#include "myxml.h"

#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomText>
#include <QTextStream>
#include <QFileInfo>

#include <QDebug>

MyXML::MyXML()
{

}

MyXML::MyXML(QString fileNmae)
{
    if(fileNmae.isEmpty())
        return;
    saveFileName = fileNmae;

    QFileInfo fileInfo(saveFileName);
    if(fileInfo.exists() && fileInfo.isFile())
        loadXML();
    else
        creatXML();
}


MyXML::~MyXML()
{

}

void MyXML::creatXML()
{
    if(saveFileName.isEmpty())
        return;

    QFile file(saveFileName);
    file.open(QIODevice::ReadWrite);

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"GB2312\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement("filelist");
    doc.appendChild(root);

    QTextStream out(&file);
    doc.save(out,4);

    file.close();
}


void MyXML::loadXML()
{
    QFile file(saveFileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        file.remove();
        creatXML();
        return;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        file.close();
        file.remove();
        creatXML();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if (root.tagName() != "filelist") {
       file.remove();
       creatXML();
    }
    qDebug()<<"root.text() = "<<root.text();
}

void MyXML::saveXMLtoFile()
{
    if(saveFileName.isEmpty())
        return;
    QFile file(saveFileName);
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

void MyXML::addElement(FileElement element)
{
    QDomElement newElement = doc.createElement("file");
    newElement.setAttribute("name", element.fileName);

    QDomElement position = doc.createElement("lastposition");
    QDomText t = doc.createTextNode(QString()+element.lastPosition);
    position.appendChild(t);
    newElement.appendChild(position);

    QDomElement playtime = doc.createElement("lastplaytime");
    t = doc.createTextNode(QString()+element.lastPlayTime);
    playtime.appendChild(t);
    newElement.appendChild(playtime);

    QDomElement root = doc.documentElement();
    root.appendChild(newElement);

}

FileElement MyXML::getElement(QString fileName)
{

}

void MyXML::removeElement(QString fileName)
{

}

void MyXML::replaceElement(FileElement element)
{

}

QStringList MyXML::getFileList()
{

}





