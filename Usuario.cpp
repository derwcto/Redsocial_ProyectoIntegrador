#include "Usuario.h"
#include <algorithm>

Publicacion::Publicacion(const std::string& contenido, const std::string& fecha, int likes)
    : contenido(contenido), fecha(fecha), likes(likes) {}

const std::string& Publicacion::getContenido() const {
    return contenido;
}

const std::string& Publicacion::getFecha() const {
    return fecha;
}

int Publicacion::getLikes() const {
    return likes;
}

void Publicacion::setContenido(const std::string& nuevoContenido) {
    contenido = nuevoContenido;
}

void Publicacion::agregarLike() {
    ++likes;
}

Usuario::Usuario(const std::string& username, const std::string& password)
    : username(username), password(password) {}

const std::string& Usuario::getUsername() const {
    return username;
}

bool Usuario::verificarPassword(const std::string& pass) const {
    return password == pass;
}

const std::vector<Publicacion>& Usuario::getPosts() const {
    return posts;
}

const std::vector<std::string>& Usuario::getAmigos() const {
    return amigos;
}

const std::vector<std::string>& Usuario::getSolicitudesPendientes() const {
    return solicitudesPendientes;
}

void Usuario::agregarPublicacion(const std::string& texto, const std::string& fecha) {
    posts.emplace_back(texto, fecha, 0);
}

bool Usuario::editarPublicacion(int indice, const std::string& nuevoTexto) {
    if (indice < 0 || static_cast<std::size_t>(indice) >= posts.size() || nuevoTexto.empty()) {
        return false;
    }
    posts[static_cast<std::size_t>(indice)].setContenido(nuevoTexto);
    return true;
}

bool Usuario::eliminarPublicacion(int indice) {
    if (indice < 0 || static_cast<std::size_t>(indice) >= posts.size()) {
        return false;
    }
    posts.erase(posts.begin() + indice);
    return true;
}

bool Usuario::darLikePublicacion(int indice) {
    if (indice < 0 || static_cast<std::size_t>(indice) >= posts.size()) {
        return false;
    }
    posts[static_cast<std::size_t>(indice)].agregarLike();
    return true;
}

bool Usuario::esAmigo(const std::string& targetUser) const {
    return std::find(amigos.begin(), amigos.end(), targetUser) != amigos.end();
}

bool Usuario::tieneSolicitudPendiente(const std::string& emisorUser) const {
    return std::find(solicitudesPendientes.begin(), solicitudesPendientes.end(), emisorUser)
           != solicitudesPendientes.end();
}

bool Usuario::recibirSolicitud(const std::string& emisorUser) {
    if (emisorUser.empty() || emisorUser == username || esAmigo(emisorUser) || tieneSolicitudPendiente(emisorUser)) {
        return false;
    }
    solicitudesPendientes.push_back(emisorUser);
    return true;
}

bool Usuario::aceptarSolicitud(const std::string& emisorUser) {
    if (!rechazarSolicitud(emisorUser)) {
        return false;
    }
    agregarAmigoDirecto(emisorUser);
    return true;
}

bool Usuario::rechazarSolicitud(const std::string& emisorUser) {
    auto it = std::find(solicitudesPendientes.begin(), solicitudesPendientes.end(), emisorUser);
    if (it == solicitudesPendientes.end()) {
        return false;
    }
    solicitudesPendientes.erase(it);
    return true;
}

void Usuario::agregarAmigoDirecto(const std::string& amigoUser) {
    if (!amigoUser.empty() && amigoUser != username && !esAmigo(amigoUser)) {
        amigos.push_back(amigoUser);
    }
}

int Usuario::calcularTotalLikes() const {
    int total = 0;
    for (const Publicacion& p : posts) {
        total += p.getLikes();
    }
    return total;
}

int Usuario::calcularPuntajeActividad() const {
    return static_cast<int>(amigos.size()) * 10
           + static_cast<int>(posts.size()) * 15
           + calcularTotalLikes() * 3;
}
