#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

class Publicacion {
private:
    std::string contenido;
    std::string fecha;
    int likes;

public:
    Publicacion(const std::string& contenido, const std::string& fecha, int likes = 0);

    const std::string& getContenido() const;
    const std::string& getFecha() const;
    int getLikes() const;

    void setContenido(const std::string& nuevoContenido);
    void agregarLike();
};

class Usuario {
private:
    std::string username;
    std::string password;
    std::vector<Publicacion> posts;
    std::vector<std::string> amigos;
    std::vector<std::string> solicitudesPendientes;

public:
    Usuario(const std::string& username, const std::string& password);

    const std::string& getUsername() const;
    bool verificarPassword(const std::string& pass) const;

    const std::vector<Publicacion>& getPosts() const;
    const std::vector<std::string>& getAmigos() const;
    const std::vector<std::string>& getSolicitudesPendientes() const;

    void agregarPublicacion(const std::string& texto, const std::string& fecha = "Hoy");
    bool editarPublicacion(int indice, const std::string& nuevoTexto);
    bool eliminarPublicacion(int indice);
    bool darLikePublicacion(int indice);

    bool esAmigo(const std::string& targetUser) const;
    bool tieneSolicitudPendiente(const std::string& emisorUser) const;
    bool recibirSolicitud(const std::string& emisorUser);
    bool aceptarSolicitud(const std::string& emisorUser);
    bool rechazarSolicitud(const std::string& emisorUser);
    void agregarAmigoDirecto(const std::string& amigoUser);

    int calcularTotalLikes() const;
    int calcularPuntajeActividad() const;
};

#endif
