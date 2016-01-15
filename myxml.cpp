#include "myxml.h"

#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomText>
#include <QTextStream>
#include <QFileInfo>
#include <QDomNodeList>

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
    if(getElement(element.fileName,NULL))
        return;
    QDomElement newElement = doc.createElement("file");
    newElement.setAttribute("name", element.fileName);

    QDomElement position = doc.createElement("lastposition");
    QDomText t = doc.createTextNode("0");
    position.appendChild(t);
    newElement.appendChild(position);

    QDomElement playtime = doc.createElement("lastplaytime");
    t = doc.createTextNode("0");
    playtime.appendChild(t);
    newElement.appendChild(playtime);

    QDomElement root = doc.documentElement();
    root.appendChild(newElement);

}

bool MyXML::getElement(QString fileName, FileElement *element)
{
    if (fileName.isEmpty())
        return false;
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        if (elt.attribute("name") == fileName) {
            if (element) {
                element->fileName = fileName;
                QDomElement lastPosition = elt.firstChildElement("lastposition");
                if(lastPosition.isNull())
                    element->lastPosition = 0;
                else
                    element->lastPosition = lastPosition.text().toLong();

                QDomElement lastPlayTime = elt.firstChildElement("lastposition");
                if(lastPlayTime.isNull())
                    element->lastPlayTime = 0;
                else
                    element->lastPlayTime = lastPlayTime.text().toLong();
            }
            return true;
        }
    }
    return false;
}

void MyXML::removeElement(QString fileName)
{

}

void MyXML::replaceElement(FileElement element)
{

}

void MyXML::getFileList(QStringList *fileList)
{
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        fileList->append(elt.attribute("name"));
    }
}





